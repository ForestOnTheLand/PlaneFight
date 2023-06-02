#pragma once

#include "util.h"
#include <functional>
#include <deque>

class BattleField;
class EnemyPlane;

class Policy {
public:
	Policy() = default;
	virtual ~Policy() = default;
	virtual void execute(BattleField* b) = 0;
	virtual bool terminal() = 0;
	virtual void draw(QPainter& painter);
};


class EnemyGeneratingPolicy : public Policy {
public:
	typedef std::function<EnemyPlane*()> plane_t;
	typedef std::function<bool()> flag_t;

private:
	int _time;
	int _timer = 0;
	// std::function<void(BattleField*)> _call;
	std::vector<std::pair<plane_t, flag_t>> _policy;

public:
	// EnemyGeneratingPolicy(const std::function<void(BattleField*)>& __f, int __time);
	EnemyGeneratingPolicy(std::initializer_list<std::pair<plane_t, flag_t>> __policy, int __time);
	void execute(BattleField* b) override;
	bool terminal() override;
};


class BossGeneratingPolicy : public Policy {
	BattleField* _field = nullptr;
	int _health, _attack;

public:
	BossGeneratingPolicy(int __health, int __attack);
	void execute(BattleField* b) final;
	bool terminal() final;
};


class EnemyClearingPolicy : public Policy {
	bool _finish = false;
	bool _start = false;

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


class MessageDisplay : public Policy {
	QString _msg;
	int _timer = 0, _time;
	BattleField* _b = nullptr;

public:
	MessageDisplay(const QString& __msg, int __time);
	void execute(BattleField* b) override;
	bool terminal() override;
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