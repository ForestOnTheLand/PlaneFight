#pragma once
#include "_Effect.h"

class TargetEffect : public _Effect {
	QPointF _pos;
	// QSoundEffect* _sound;

public:
	explicit TargetEffect(const QPointF& __pos);
	~TargetEffect();
	void display(QPainter& painter) final;
};
