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
	virtual void draw(QPainter& painter);
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

class PictureDisplay : public Policy {
	std::vector<std::pair<const char* const, QPoint>> _list;
	std::vector<std::pair<QPixmap, QRect>> _picture;
	int _time;
	int _timer = 0;

public:
	PictureDisplay(std::initializer_list<std::pair<const char* const, QPoint>> __list, int __time);
	void execute(BattleField* b) override;
	bool terminal() override;
	void draw(QPainter& painter) override;
};

class EnemyGenerator {
protected:
	std::deque<Policy*> _policies;
	bool _free = false;

public:
	EnemyGenerator(std::initializer_list<Policy*> __policies);
	~EnemyGenerator();
	void execute(BattleField* b);
	bool free() const;
	void draw(QPainter& painter) const;
};