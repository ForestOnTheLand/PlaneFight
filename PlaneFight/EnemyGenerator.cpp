#include "EnemyGenerator.h"
#include "BattleField.h"
#include "BossEnemyPlane.h"

void Policy::draw(QPainter& painter) {
	return;
}

EnemyGeneratingPolicy::EnemyGeneratingPolicy(const std::function<void(BattleField*)>& __f,
                                             int __time)
    : _call(__f), _time(__time * (1000 / update_rate)) {}


void EnemyGeneratingPolicy::execute(BattleField* b) {
	_call(b);
	++_timer;
}
bool EnemyGeneratingPolicy::terminal() {
	return _timer > _time;
}

void EnemyClearingPolicy::execute(BattleField* b) {
	if (b->_enemies.empty()) {
		_finish = true;
	} else {
		for (_EnemyPlane* enemy : b->_enemies) {
			enemy->_rect.moveCenter({0, 10});
		}
	}
}
bool EnemyClearingPolicy::terminal() {
	return _finish;
}

void BossGeneratingPolicy::execute(BattleField* b) {
	if (!_field) {
		_field = b;
		_field->_enemies.push_back(new BossEnemyPlane(":/PlaneFight/img/enemy.png", 10000));
	}
}
bool BossGeneratingPolicy::terminal() {
	return _field != nullptr && _field->_enemies.empty();
}


PictureDisplay::PictureDisplay(std::initializer_list<std::pair<const char* const, QPoint>> __list,
                               int __time)
    : _time(__time * (1000 / update_rate)), _list(__list) {}
void PictureDisplay::execute(BattleField* b) {
	++_timer;
}
bool PictureDisplay::terminal() {
	return _timer > _time;
}
void PictureDisplay::draw(QPainter& painter) {
	if (_list.size() != _picture.size()) {
		for (auto [path, pos] : _list) {
			QPixmap picture;
			picture.load(path);
			_picture.push_back(
			    {picture, QRect(pos.x() - picture.width() / 2, pos.y() - picture.height() / 2,
			                    picture.width(), picture.height())});
		}
	} else {
		for (auto [pixmap, rect] : _picture) {
			painter.drawPixmap(rect, pixmap);
		}
	}
}


EnemyGenerator::EnemyGenerator(std::initializer_list<Policy*> __policies) : _policies(__policies) {}
EnemyGenerator::~EnemyGenerator() {
	for (Policy* policy : _policies) {
		delete policy;
	}
}

void EnemyGenerator::execute(BattleField* b) {
	if (_policies.empty()) {
		_free = true;
	} else if (!_policies.front()->terminal()) {
		_policies.front()->execute(b);
	} else {
		delete _policies.front();
		_policies.pop_front();
	}
}
bool EnemyGenerator::free() const {
	return _free;
}
void EnemyGenerator::draw(QPainter& painter) const {
	if (!_policies.empty())
		_policies.front()->draw(painter);
}
