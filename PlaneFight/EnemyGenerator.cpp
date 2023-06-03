#include "EnemyGenerator.h"
#include "BattleField.h"
#include "BossEnemyPlane.h"

void Policy::draw(QPainter& painter) {
	return;
}

EnemyGeneratingPolicy::EnemyGeneratingPolicy(
    std::initializer_list<std::pair<plane_t, flag_t>> __policy, int __time)
    : _policy(__policy), _time(__time * (1000 / update_rate)) {}

void EnemyGeneratingPolicy::execute(BattleField* b) {
	for (auto& [plane, flag] : _policy) {
		if (flag()) {
			b->enemy_planes.push_back(plane());
		}
	}
	++_timer;
}
bool EnemyGeneratingPolicy::terminal() {
	return _timer > _time;
}
void EnemyGeneratingPolicy::reset() {
	_timer = 0;
}

void EnemyClearingPolicy::execute(BattleField* b) {
	if (b->enemy_planes.empty()) {
		_finish = true;
	} else if (!_start) {
		_start = true;
		for (_EnemyPlane* enemy : b->enemy_planes) {
			enemy->_clearOut();
		}
	}
}
bool EnemyClearingPolicy::terminal() {
	return _finish;
}

void EnemyClearingPolicy::reset() {
	_finish = false, _start = false;
}

BossGeneratingPolicy::BossGeneratingPolicy(const char* __img_path, int __health, int __attack)
    : _health(__health), _attack(__attack), _img_path(__img_path) {}
void BossGeneratingPolicy::execute(BattleField* b) {
	if (!_field) {
		_field = b;
		_field->enemy_planes.push_back(new BossEnemyPlane(_img_path, _health, _attack));
	}
}
bool BossGeneratingPolicy::terminal() {
	return _field && _field->enemy_planes.empty();
}
void BossGeneratingPolicy::reset() {
	_field = nullptr;
}


PictureDisplay::PictureDisplay(std::initializer_list<std::pair<const char* const, QPointF>> __list,
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
		for (auto& [path, pos] : _list) {
			QPixmap picture;
			picture.load(path);
			_picture.push_back(
			    {picture, QRectF(pos.x() - picture.width() / 2.0, pos.y() - picture.height() / 2.0,
			                     picture.width(), picture.height())});
		}
	} else {
		for (auto& [pixmap, rect] : _picture) {
			painter.drawPixmap(rect, pixmap, QRectF());
		}
	}
}

void PictureDisplay::reset() {
	_timer = 0;
}


EnemyGenerator::EnemyGenerator(std::initializer_list<Policy*> __policies, bool __repeat)
    : _policies(__policies), _repeat(__repeat) {}
EnemyGenerator::~EnemyGenerator() {
	for (Policy* policy : _policies) {
		delete policy;
	}
}


MessageDisplay::MessageDisplay(const QString& __msg, int __time)
    : _msg(__msg), _time(__time * (1000 / update_rate)) {}
void MessageDisplay::execute(BattleField* b) {
	if (!_b) {
		_b = b;
		_b->ui->msg_label->setText(_msg);
	}
}
bool MessageDisplay::terminal() {
	if (++_timer > _time) {
		_b->ui->msg_label->setText(" ");
		return true;
	} else {
		return false;
	}
}

void MessageDisplay::reset() {
	_timer = 0;
	_b = nullptr;
}


void EnemyGenerator::execute(BattleField* b) {
	if (_policies.empty()) {
		_free = true;
	} else if (_policies.front()->terminal()) {
		if (_repeat) {
			_policies.front()->reset();
			_policies.push_back(_policies.front());
		} else {
			delete _policies.front();
		}
		_policies.pop_front();
	} else {
		_policies.front()->execute(b);
	}
}
bool EnemyGenerator::free() const {
	return _free;
}
void EnemyGenerator::draw(QPainter& painter) const {
	if (!_policies.empty())
		_policies.front()->draw(painter);
}
