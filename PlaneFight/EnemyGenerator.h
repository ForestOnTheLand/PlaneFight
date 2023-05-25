#pragma once

#include "util.h"
#include <functional>
#include <deque>

class BattleField;

class Policy {
public:
	Policy() = default;
	virtual ~Policy() = default;
	virtual void execute(BattleField* b) = 0;
	virtual bool terminal() = 0;
};


class EnemyGeneratingPolicy : public Policy {
	int _time;
	int _timer = 0;
	std::function<void(BattleField*)> _call;

public:
	EnemyGeneratingPolicy(const std::function<void(BattleField*)>& __f, int __time);
	void execute(BattleField* b) override;
	bool terminal() override;
};


class BossGeneratingPolicy : public Policy {
	BattleField* _field = nullptr;

public:
	BossGeneratingPolicy() = default;
	void execute(BattleField* b) final;
	bool terminal() final;
};


class EnemyClearingPolicy : public Policy {
	bool _finish = false;

public:
	EnemyClearingPolicy() = default;
	void execute(BattleField* b) override;
	bool terminal() override;
};


class EnemyGenerator {
protected:
	std::deque<Policy*> _policies;
	bool _free = false;

public:
	EnemyGenerator(std::initializer_list<Policy*> __policies);
	void execute(BattleField* b);
	bool free() const;
};
