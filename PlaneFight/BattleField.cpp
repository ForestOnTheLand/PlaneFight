#include "BattleField.h"
#include "PlayerPlane.h"
#include "EnemyPlane.h"

static constexpr const char* enemy_plane_path = ":/PlaneFight/img/enemy.png";    // @IMAGE

BattleField::BattleField(QWidget* parent)
    : QWidget(parent), ui(new Ui::BattleFieldClass()), _timer(new QTimer) {
	score = 0;
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
	_timer->setInterval(UPDATE_RATE);
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
	for (auto iter = _enemyDrop.begin(); iter != _enemyDrop.end();) {
		if ((*iter)->free()) {
			delete* iter;
			iter = _enemyDrop.erase(iter);
		}
		else {
			(*iter)->updatePosition();
			++iter;
		}
	}
}

void BattleField::checkDeadPlane() {
	for (auto iter = _enemies.begin(); iter != _enemies.end();) {
		if ((*iter)->dead() || (*iter)->out()) {
			if ((*iter)->dead()) {
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
	for (_Missile* drop : _enemyDrop) {
		drop->collide(PlayerPlane::plane());
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
			delete* iter;
			iter = _enemyMissile.erase(iter);
		}
		_key.K = 0;
	}
}


void BattleField::paintEvent(QPaintEvent* _event) {
	QPainter painter(this);
	painter.drawRect(battlefield_border);
	painter.drawPixmap(PlayerPlane::plane()->rect(), PlayerPlane::plane()->picture());
	for (EnemyPlane* enemy : _enemies) {
		painter.drawPixmap(enemy->rect(), enemy->picture());
	}
	PlayerPlane::plane()->drawMissiles(painter);
	for (_Missile* missile : _enemyMissile) {
		// painter.drawRect(missile->rect());
		painter.drawPixmap(missile->rect(), missile->picture());
	}
	for (_Missile* drop : _enemyDrop) {
		painter.drawPixmap(drop->rect(), drop->picture());
	}
	paintEffect(painter);
	painter.drawText(700, 200, QString::number(score,10));
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
			case Qt::Key_Escape: gameOver(); break;
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
			case Qt::Key_Escape: gameOver(); break;
			default: break;
		}
	}
}
