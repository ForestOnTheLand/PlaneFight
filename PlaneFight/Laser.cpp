#include "Laser.h"
#include "PlayerPlane.h"
#include <qdebug.h>

void Laser::hurt() {
	static int _hurt_timer = 0;
	if (_hurt_timer > 0) {
		--_hurt_timer;
	}
	if (QPolygon({src, QPoint(src.x() + 1000 * cos(theta), src.y() + 1000 * sin(theta))})
	        .intersects(PlayerPlane::plane()->rect())) {
		PlayerPlane::plane()->health() -= 100;
		_hurt_timer = 50;    // Ensure no hurt in 50 ticks
	}
}

void Laser::drawOn(QPainter& painter) {
	QPen pen = painter.pen(), _pen = pen;
	pen.setWidth(_width);
	pen.setColor(Qt::white);
	painter.setPen(pen);
	QRectF rect = painter.clipBoundingRect();
	painter.setClipRect(battlefield_border);
	painter.drawLine(src, QPoint(src.x() + 1000 * cos(theta), src.y() + 1000 * sin(theta)));
	painter.setPen(_pen);
	painter.setClipRect(rect);
}
