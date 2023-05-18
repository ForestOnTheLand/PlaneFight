#include "BattleField.h"
#include "PlayerPlane.h"

BattleField::BattleField(QWidget* parent)
    : QWidget(parent), ui(new Ui::BattleFieldClass()), _timer(new QTimer) {
	ui->setupUi(this);
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
		EnemyPlane* enemy = new TrivialEnemyPlane("");
		enemy->setPosition(rand() % BATTLEFIELD_WIDTH, 10);
		_enemies.push_back(enemy);
	}
}

void BattleField::updateAll() {
	PlayerPlane::plane()->shootMissiles();
	PlayerPlane::plane()->updateMissiles();
	generateEnemy();
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

void BattleField::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.drawPixmap(PlayerPlane::plane()->rect(), PlayerPlane::plane()->picture());
	for (EnemyPlane* enemy : _enemies) {
		painter.drawPixmap(enemy->rect(), enemy->picture());
	}
	PlayerPlane::plane()->drawMissiles(painter);
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
