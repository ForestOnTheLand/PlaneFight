#pragma once
#include "_Effect.h"

class ExplosionEffect : public _Effect {
	QPoint _pos;
	QSoundEffect* _sound;

public:
	explicit ExplosionEffect(const QPoint& __pos);
	~ExplosionEffect();
	void display(QPainter& painter) final;
};
