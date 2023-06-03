#include "BattleField.h"
#include "PlayerPlane.h"
#include "Menu.h"
#include "GameReview.h"
#include "LevelReview.h"
#include <QtMultimedia/qsoundeffect.h>
#include <algorithm>
#include <QDebug>
#include "Generator.h"

BattleField::BattleField(QWidget* parent, Menu* menu)
    : QWidget(parent), ui(new Ui::BattleFieldClass()), _timer(new QTimer), _generator(nullptr),
      mainMenu(menu) {
	ui->setupUi(this);
	this->setAutoFillBackground(true);
	this->setFixedSize(800, 800);
	pic1.load(":/PlaneFight/img/battleBackground.jpg");
	pic2.load(":/PlaneFight/img/background22.png");
	// start();
}

BattleField::~BattleField() {
	PlayerPlane::free();
	delete ui;
	delete _timer;
	delete _generator;
}

void BattleField::start(int level) {
	PlayerPlane::init(this);
	_generator = Generator::level(level);
	_timer->setInterval(update_rate);
	setMouseTracking(true);
	_timer->start();

	connect(_timer, &QTimer::timeout, [=]() {
		updateAll();
		update();
	});
}

void BattleField::updateAll() {
	PlayerPlane::plane()->shootMissiles();
	PlayerPlane::plane()->updateMissiles();
	processKeyEvent();
	generateEnemy();
	checkCollision();
	checkDeadPlane();
	for (_EnemyPlane* enemy : enemy_planes) {
		enemy->updatePosition();
		enemy->shootMissiles(this);
	}
	updateMissiles();
	updateDrops();
}

void BattleField::gameOver() {
	_timer->stop();
	if (mainMenu->mode == 0) {
		GameReview* pGameReview = qobject_cast<GameReview*>(mainMenu->gameWidgets[5]);
		pGameReview->score = PlayerPlane::plane()->score;
		pGameReview->refill();
		mainMenu->stackWidget->setCurrentIndex(5);
	}
	else {
		LevelReview* pLevelReview = qobject_cast<LevelReview*>(mainMenu->gameWidgets[7]);
		pLevelReview->score = PlayerPlane::plane()->score;
		pLevelReview->refill(0);
		mainMenu->stackWidget->setCurrentIndex(7);
	}
	mainMenu->to_remove.push_back(mainMenu->gameWidgets[2]);
	mainMenu->gameWidgets[2] = new BattleField(nullptr, mainMenu);
	mainMenu->stackWidget->insertWidget(2, mainMenu->gameWidgets[2]);
	mainMenu->stackWidget->removeWidget(this);
}

void BattleField::pause() {
	_timer->isActive() ? _timer->stop() : _timer->start();
}

void BattleField::generateEnemy() {
	_generator->execute(this);
	if (_generator->free())
		gameWin();
}

void BattleField::gameWin() {
		
	LevelReview* pLevelReview = qobject_cast<LevelReview*>(mainMenu->gameWidgets[7]);
	pLevelReview->score = PlayerPlane::plane()->score;
	pLevelReview->refill(1);
	mainMenu->stackWidget->setCurrentIndex(7);

	mainMenu->to_remove.push_back(mainMenu->gameWidgets[2]);
	mainMenu->gameWidgets[2] = new BattleField(nullptr, mainMenu);
	mainMenu->stackWidget->insertWidget(2, mainMenu->gameWidgets[2]);
	mainMenu->stackWidget->removeWidget(this);
	gameOver();
}

void BattleField::updateMissiles() {
	enemy_missiles.erase(std::copy_if(enemy_missiles.begin(), enemy_missiles.end(),
	                                  enemy_missiles.begin(),
	                                  [](_Missile* missile) -> bool {
		                                  if (missile->free()) {
			                                  delete missile;
			                                  return false;
		                                  } else {
			                                  missile->updatePosition();
			                                  return true;
		                                  }
	                                  }),
	                     enemy_missiles.end());
}

void BattleField::updateDrops() {
	for (auto iter = drops.begin(); iter != drops.end();) {
		if ((*iter)->free()) {
			delete *iter;
			iter = drops.erase(iter);
		} else {
			(*iter)->updatePosition();
			++iter;
		}
	}
}

void BattleField::checkDeadPlane() {
	for (auto iter = enemy_planes.begin(); iter != enemy_planes.end();) {
		if ((*iter)->dead() || (*iter)->out()) {
			if ((*iter)->dead()) {
				PlayerPlane::plane()->score += 100;
				// effects.push_back(new ExplosionEffect((*iter)->rect().center()));
				(*iter)->afterDeath(this);
			}
			delete *iter;
			iter = enemy_planes.erase(iter);
		} else {
			++iter;
		}
	}
	if (PlayerPlane::plane()->dead())
		gameOver();
}

void BattleField::checkCollision() {
	for (_EnemyPlane* enemy : enemy_planes) {
		enemy->hurt(PlayerPlane::plane());
		PlayerPlane::plane()->hurt(enemy);
	}
	for (_Missile* missile : enemy_missiles) {
		missile->collide(PlayerPlane::plane());
	}
	for (_Bonus* drop : drops) {
		drop->collide();
	}
}

void BattleField::paintEffect(QPainter& painter) {
	for (auto iter = effects.begin(); iter != effects.end();) {
		if ((*iter)->valid()) {
			(*iter)->display(painter);
			++iter;
		} else {
			delete *iter;
			iter = effects.erase(iter);
		}
	}
}

void BattleField::processKeyEvent() {
	if (_key.W)
		PlayerPlane::plane()->moveBy(0, -3);
	if (_key.A)
		PlayerPlane::plane()->moveBy(-3, 0);
	if (_key.S)
		PlayerPlane::plane()->moveBy(0, 3);
	if (_key.D)
		PlayerPlane::plane()->moveBy(3, 0);
	if (_key.K) {
		PlayerPlane::plane()->Bomb();
		for (auto iter = enemy_missiles.begin(); iter != enemy_missiles.end();) {
			delete *iter;
			iter = enemy_missiles.erase(iter);
		}
		_key.K = 0;
	}
}


void BattleField::paintEvent(QPaintEvent* _event) {
	QPainter painter(this);
	/*painter.setBrush(Qt::gray);
	painter.drawRect(this->rect());
	painter.setBrush(Qt::NoBrush);*/
	painter.drawPixmap(battlefield_border, pic2, QRectF());
	painter.drawRect(battlefield_border);
	painter.setClipRect(battlefield_border);
	PlayerPlane::plane()->drawOn(painter);
	for (_EnemyPlane* enemy : enemy_planes) {
		enemy->drawOn(painter);
	}
	for (_Missile* missile : enemy_missiles) {
		painter.drawPixmap(missile->rect(), missile->picture(), QRectF());
	}
	for (_Bonus* drop : drops) {
		painter.drawPixmap(drop->rect(), drop->picture(), QRectF());
	}
	paintEffect(painter);
	_generator->draw(painter);
	ui->score_label->setText(QString("Score: ") + QString::number(PlayerPlane::plane()->score));
	ui->hp_label->setText(QString("HP: ") + QString::number(PlayerPlane::plane()->health()) + "/" +
	                      QString::number(player_max_health));
	ui->bomb_label->setText(QString("Bomb: ") + QString::number(PlayerPlane::plane()->bombs) +
	                        "/3");
	ui->score_label->setStyleSheet("color:rgb(255,0,0)");
	ui->hp_label->setStyleSheet("color:rgb(255,0,0)");
	ui->bomb_label->setStyleSheet("color:rgb(255,0,0)");
}

void BattleField::mouseMoveEvent(QMouseEvent* _event) {
	if (play_mode == mouse_mode) {
		int x = _event->x(), y = _event->y();
		PlayerPlane::plane()->setPosition(x, y);
	}
}

void BattleField::keyPressEvent(QKeyEvent* _event) {
	if (play_mode == key_mode) {
		switch (_event->key()) {
			case Qt::Key_K: _key.K = true; break;
			case Qt::Key_W: _key.W = true; break;
			case Qt::Key_A: _key.A = true; break;
			case Qt::Key_S: _key.S = true; break;
			case Qt::Key_D: _key.D = true; break;
			case Qt::Key_L: PlayerPlane::plane()->shootUltimate(); break;
			case Qt::Key_Escape: pause(); break;
			case Qt::Key_Backspace: gameOver(); break;
			default: break;
		}
	}
}

void BattleField::keyReleaseEvent(QKeyEvent* _event) {
	if (play_mode == key_mode) {
		switch (_event->key()) {
			case Qt::Key_W: _key.W = false; break;
			case Qt::Key_A: _key.A = false; break;
			case Qt::Key_S: _key.S = false; break;
			case Qt::Key_D: _key.D = false; break;
			case Qt::Key_Escape: break;
			default: break;
		}
	}
}
