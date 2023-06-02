#include "Laser.h"
#include "PlayerPlane.h"
#include <qdebug.h>
#include <qtransform.h>

Laser::Laser() {
	_picture.load(":/PlaneFight/img/laser_0.png");
}

void Laser::hurt() {
	static int _hurt_timer = 0;
	if (_hurt_timer > 0) {
		--_hurt_timer;
	}
	if (QPolygonF({src, QPoint(src.x() + 1000 * cos(theta), src.y() + 1000 * sin(theta))})
	        .intersects(PlayerPlane::plane()->rect())) {
		PlayerPlane::plane()->health() -= 100;
		_hurt_timer = 50;    // Ensure no hurt in 50 ticks
	}
}

void Laser::drawOn(QPainter& painter) {
	painter.save();
	QTransform transform;
	transform.translate(src.x(), src.y());
	transform.rotate(to_deg(theta));
	painter.setWorldTransform(transform);
	painter.drawPixmap(QPointF(10, -_picture.height() / 2.0), _picture);
	painter.restore();
}
