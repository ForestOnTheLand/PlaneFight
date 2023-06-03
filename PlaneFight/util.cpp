#include "util.h"
#include <QTransform>

void paintRotatedPicture(QPainter& painter, const QPixmap& picture, QPointF center, double deg) {
	painter.save();
	QTransform transform;
	transform.translate(center.x(), center.y());
	transform.rotate(deg);
	painter.setTransform(transform);
	painter.drawPixmap(picture.width() / 2, picture.height() / 2, picture);
	painter.restore();
}
