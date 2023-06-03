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
	virtual void reset() = 0;
};


class EnemyGeneratingPolicy : public Policy {
public:
	typedef std::function<EnemyPlane*()> plane_t;
	typedef std::function<bool()> flag_t;

private:
	int _time;
	int _timer = 0;
	std::vector<std::pair<plane_t, flag_t>> _policy;

public:
	EnemyGeneratingPolicy(std::initializer_list<std::pair<plane_t, flag_t>> __policy, int __time);
	void execute(BattleField* b) override;
	bool terminal() override;
	void reset() final;
};


class BossGeneratingPolicy : public Policy {
	BattleField* _field = nullptr;
	const int _health, _attack;
	const char* _img_path;

public:
	BossGeneratingPolicy(const char* __img_path, int __health, int __attack);
	void execute(BattleField* b) final;
	bool terminal() final;
	void reset() final;
};


class EnemyClearingPolicy : public Policy {
	bool _finish = false;
	bool _start = false;

public:
	EnemyClearingPolicy() = default;
	void execute(BattleField* b) override;
	bool terminal() override;
	void reset() final;
};


class PictureDisplay : public Policy {
	std::vector<std::pair<const char* const, QPointF>> _list;
	std::vector<std::pair<QPixmap, QRectF>> _picture;
	int _time;
	int _timer = 0;

public:
	PictureDisplay(std::initializer_list<std::pair<const char* const, QPointF>> __list, int __time);
	void execute(BattleField* b) override;
	bool terminal() override;
	void draw(QPainter& painter) override;
	void reset() final;
};


class MessageDisplay : public Policy {
	QString _msg;
	int _timer = 0, _time;
	BattleField* _b = nullptr;

public:
	MessageDisplay(const QString& __msg, int __time);
	void execute(BattleField* b) override;
	bool terminal() override;
	void reset() final;
};


class EnemyGenerator {
protected:
	std::deque<Policy*> _policies;
	bool _free = false;
	bool _repeat;

public:
	EnemyGenerator(std::initializer_list<Policy*> __policies, bool __repeat = false);
	~EnemyGenerator();
	void execute(BattleField* b);
	bool free() const;
	void draw(QPainter& painter) const;
};