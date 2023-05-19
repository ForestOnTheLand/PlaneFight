#include "BattleField.h"
#include "PlayerPlane.h"

static constexpr const char* enemy_plane_path = ":/PlaneFight/img/enemy.png";    // @IMAGE

BattleField::BattleField(QWidget* parent)
    : QWidget(parent), ui(new Ui::BattleFieldClass()), _timer(new QTimer) {
	ui->setupUi(this);
	this->setFixedSize(BATTLEFIELD_WIDTH, BATTLEFIELD_HEIGHT);
	PlayerPlane::init();
	start();
}

BattleField::~BattleField() {
	PlayerPlane::free();
	delete ui;
	delete _timer;
}

void BattleField::generateEnemy() {
	static int timer = 0;
	if (++timer >= 100) {
		timer = 0;
		EnemyPlane* enemy = new TrivialEnemyPlane(enemy_plane_path, 50);
		enemy->setPosition(rand() % BATTLEFIELD_WIDTH, 10);
		_enemies.push_back(enemy);
	}
}

void BattleField::checkDeadPlane() {
	for (auto iter = _enemies.begin(); iter != _enemies.end();) {
		if ((*iter)->dead()) {
			_effects.push_back(new ExplosionEffect((*iter)->rect().center()));
			delete *iter;
			iter = _enemies.erase(iter);
		} else {
			++iter;
		}
	}
	if (PlayerPlane::plane()->dead())
		gameOver();
}

void BattleField::updateAll() {
	PlayerPlane::plane()->shootMissiles();
	PlayerPlane::plane()->updateMissiles();
	generateEnemy();
	checkCollision();
	checkDeadPlane();
	for (EnemyPlane* enemy : _enemies) {
		enemy->updatePosition();
	}
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

void BattleField::checkCollision() {
	for (EnemyPlane* enemy : _enemies) {
		enemy->hurt(PlayerPlane::plane());
		PlayerPlane::plane()->hurt(enemy);
	}
}

void BattleField::gameOver() {
	exit(0);
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

void BattleField::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.drawPixmap(PlayerPlane::plane()->rect(), PlayerPlane::plane()->picture());
	for (EnemyPlane* enemy : _enemies) {
		painter.drawPixmap(enemy->rect(), enemy->picture());
	}
	PlayerPlane::plane()->drawMissiles(painter);
	paintEffect(painter);
}

void BattleField::mouseMoveEvent(QMouseEvent* event) {
	int x = event->x(), y = event->y();

	if (x <= 0)
		x = 0;
	else if (x >= BATTLEFIELD_WIDTH)
		x = BATTLEFIELD_WIDTH;

	if (y <= 0)
		y = 0;
	else if (y >= BATTLEFIELD_HEIGHT)
		y = BATTLEFIELD_HEIGHT;

	PlayerPlane::plane()->setPosition(x, y);
}
