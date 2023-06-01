#pragma once
#include "_Effect.h"

class TargetEffect : public _Effect {
	QPoint _pos;
	//QSoundEffect* _sound;

public:
	explicit TargetEffect(const QPoint& __pos);
	~TargetEffect();
	void display(QPainter& painter) final;
};
