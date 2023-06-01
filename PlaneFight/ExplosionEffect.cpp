#include "ExplosionEffect.h"
#include <QtMultimedia/QSoundEffect>

ExplosionEffect::ExplosionEffect(const QPoint& __pos)
    : _Effect({":/PlaneFight/img/explosion_1.png", ":/PlaneFight/img/explosion_2.png"}),
      _pos(__pos) {
	_sound = new QSoundEffect();
	_sound->setSource(QUrl::fromLocalFile(":/PlaneFight/sound/effect_sound/se_enep00.wav"));
	_sound->play();
}

ExplosionEffect::~ExplosionEffect() {
	delete _sound;
}

void ExplosionEffect::display(QPainter& painter) {
	if (++_timer == 10) {
		_timer = 0;
		if (++_picture_index == _pictures.size()) {
			_valid = false;
			return;
		}
	}
	QPixmap& picture = *_pictures[_picture_index];
	painter.drawPixmap(_pos.x() - picture.width() / 2, _pos.y() - picture.height() / 2, picture);
}
