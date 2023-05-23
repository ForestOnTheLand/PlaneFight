#include "BattleField.h"
#include "PlayerPlane.h"
#include "EnemyPlane.h"

static constexpr const char* enemy_plane_path = ":/PlaneFight/img/enemy.png";    // @IMAGE

BattleField::BattleField(QWidget* parent)
    : QWidget(parent), ui(new Ui::BattleFieldClass()), _timer(new QTimer) {
	ui->setupUi(this);
	this->setFixedSize(800, 800);
	PlayerPlane::init();
	start();
}

BattleField::~BattleField() {
	PlayerPlane::free();
	delete ui;
	delete _timer;
}

void BattleField::start() {
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
	for (EnemyPlane* enemy : _enemies) {
		enemy->updatePosition();
		enemy->shootMissiles(this);
	}
	updateMissiles();
	updateDrops();
}

void BattleField::gameOver() {
	exit(0);
}

void BattleField::pause() {
	_timer->isActive() ? _timer->stop() : _timer->start();
}

void BattleField::generateEnemy() {
	static int timer = 0;
	if (++timer >= 60) {
		timer = 0;
		EnemyPlane* enemy = new TrivialEnemyPlane(enemy_plane_path, 60);
		enemy->setPosition(randint(battlefield_border.left(), battlefield_border.right()), 10);
		_enemies.push_back(enemy);
	}
}

void BattleField::updateMissiles() {
	for (auto iter = _enemyMissile.begin(); iter != _enemyMissile.end();) {
		if ((*iter)->free()) {
			delete *iter;
			iter = _enemyMissile.erase(iter);
		} else {
			(*iter)->updatePosition();
			++iter;
		}
	}
}

void BattleField::updateDrops() {
	for (auto iter = _drops.begin(); iter != _drops.end();) {
		if ((*iter)->free()) {
			delete *iter;
			iter = _drops.erase(iter);
		} else {
			(*iter)->updatePosition();
			++iter;
		}
	}
}

void BattleField::checkDeadPlane() {
	for (auto iter = _enemies.begin(); iter != _enemies.end();) {
		if ((*iter)->dead() || (*iter)->out()) {
			if ((*iter)->dead()) {
				PlayerPlane::plane()->score += 100;
				_effects.push_back(new ExplosionEffect((*iter)->rect().center()));
				(*iter)->Drop(this);
			}
			delete *iter;
			iter = _enemies.erase(iter);
		} else {
			++iter;
		}
	}
	if (PlayerPlane::plane()->dead())
		gameOver();
}

void BattleField::checkCollision() {
	for (EnemyPlane* enemy : _enemies) {
		enemy->hurt(PlayerPlane::plane());
		PlayerPlane::plane()->hurt(enemy);
	}
	for (_Missile* missile : _enemyMissile) {
		missile->collide(PlayerPlane::plane());
	}
	for (_Bonus* drop : _drops) {
		drop->collide();
	}
}

void BattleField::paintEffect(QPainter& painter) {
	for (auto iter = _effects.begin(); iter != _effects.end();) {
		if ((*iter)->valid()) {
			(*iter)->display(painter);
			++iter;
		} else {
			delete *iter;
			iter = _effects.erase(iter);
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
		for (auto iter = _enemyMissile.begin(); iter != _enemyMissile.end();) {
			delete *iter;
			iter = _enemyMissile.erase(iter);
		}
		_key.K = 0;
	}
}


void BattleField::paintEvent(QPaintEvent* _event) {
	QPainter painter(this);
	painter.drawRect(battlefield_border);
	painter.drawPixmap(PlayerPlane::plane()->rect(), PlayerPlane::plane()->picture());
	PlayerPlane::plane()->drawMissiles(painter);
	PlayerPlane::plane()->drawHP(painter);
	for (EnemyPlane* enemy : _enemies) {
		painter.drawPixmap(enemy->rect(), enemy->picture());
	}
	for (_Missile* missile : _enemyMissile) {
		painter.drawPixmap(missile->rect(), missile->picture());
	}
	for (_Bonus* drop : _drops) {
		painter.drawPixmap(drop->rect(), drop->picture());
	}
	paintEffect(painter);

	ui->score_label->setText(QString("Score: ") + QString::number(PlayerPlane::plane()->score));
	ui->hp_label->setText(QString("HP: ") + QString::number(PlayerPlane::plane()->health()) + "/" +
	                      QString::number(player_max_health));
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
