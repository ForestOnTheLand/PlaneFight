#pragma once

#include "util.h"

#include <vector>
#include <initializer_list>

/**
 * Abstract base class for all effects, including pictures/sound.
 */
class _Effect {
protected:
	std::vector<QPixmap*> _pictures;
	bool _valid;
	int _picture_index;
	int _timer;

public:
	_Effect(std::initializer_list<const char*> __images_path);
	bool valid() const;
	virtual ~_Effect();
	virtual void update();
	virtual void display(QPainter& painter) = 0;
};
