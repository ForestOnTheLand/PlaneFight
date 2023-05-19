#pragma once
#include "_Effect.h"

class ExplosionEffect : public _Effect {
	QPoint _pos;

public:
	explicit ExplosionEffect(const QPoint& __pos);
	void display(QPainter& painter) final;
};
