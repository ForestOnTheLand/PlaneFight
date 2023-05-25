#include "EnemyGenerator.h"
#include "BattleField.h"
#include "BossEnemyPlane.h"

EnemyGeneratingPolicy::EnemyGeneratingPolicy(const std::function<void(BattleField*)>& __f,
                                             int __time)
    : _call(__f), _time(__time * update_rate) {}
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
		for (EnemyPlane* enemy : b->_enemies) {
			enemy->moveBy(0, 10);
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

EnemyGenerator::EnemyGenerator(std::initializer_list<Policy*> __policies) : _policies(__policies) {}
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
