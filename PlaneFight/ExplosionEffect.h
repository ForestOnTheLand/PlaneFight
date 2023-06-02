#pragma once
#include "_Effect.h"
class QSoundEffect;

class ExplosionEffect : public _Effect {
	QPointF _pos;
	QSoundEffect* _sound;

public:
	explicit ExplosionEffect(const QPointF& __pos);
	~ExplosionEffect();
	void display(QPainter& painter) final;
};
