#include "PlayerPlane.h"
#include "SteadyMissile.h"

static constexpr const char* player_plane_path = ":/PlaneFight/img/player.png";         // @IMAGE
static constexpr const char* player_missile_path = ":/PlaneFight/img/missile_0.png";    // @IMAGE
static constexpr const char* player_bomb_path =
    ":/PlaneFight/img/bullet/scale_bullet_red.png";    // @IMAGE

static constexpr int player_plane_shoot_interval_1 = 20;
static constexpr int player_plane_shoot_interval_2 = 20;
static constexpr int player_plane_shoot_interval_3 = 20;
static constexpr int player_plane_bombs = 3;

PlayerPlane* PlayerPlane::_plane = nullptr;

PlayerPlane::PlayerPlane(const char* const __image_path, int _bombs)
    : _Plane(__image_path, player_max_health), bombs(_bombs), score(0), power(0) {}

void PlayerPlane::init() {
	_plane = new PlayerPlane(player_plane_path, player_plane_bombs);
	_plane->setPosition(battlefield_border.center().x(),
	                    battlefield_border.bottom() - _plane->rect().height());
}


void PlayerPlane::_setPosition(int __x, int __y) {
	_rect.moveCenter({_checked(__x, battlefield_border.left() + _rect.width() / 2,
	                           battlefield_border.right() - _rect.width() / 2),
	                  _checked(__y, battlefield_border.top() + _rect.height() / 2,
	                           battlefield_border.bottom() - _rect.height() / 2)});
}


void PlayerPlane::free() {
	delete _plane;
	_plane = nullptr;
}

void PlayerPlane::shootMissiles() {
	static int timer = 0;
	switch (power / 5) {
		case 0:
			if (++timer >= player_plane_shoot_interval_1) {
				timer = 0;
				_missiles.push_back(new SteadyMissile(player_missile_path, _rect.center().x(),
				                                      _rect.center().y() - 20, 0, -10, 50));
			}
			break;
		case 1:
			if (++timer >= player_plane_shoot_interval_2) {
				timer = 0;
				_missiles.push_back(new SteadyMissile(player_missile_path, _rect.center().x() - 10,
				                                      _rect.center().y() - 20, 0, -10, 50));
				_missiles.push_back(new SteadyMissile(player_missile_path, _rect.center().x() + 10,
				                                      _rect.center().y() - 20, 0, -10, 50));
			}
			break;
		default:
			if (++timer >= player_plane_shoot_interval_3) {
				timer = 0;
				_missiles.push_back(new SteadyMissile(player_missile_path, _rect.center().x() - 5,
				                                      _rect.center().y() - 20, 0, -10, 50));
				_missiles.push_back(new SteadyMissile(player_missile_path, _rect.center().x() + 5,
				                                      _rect.center().y() - 20, 0, -10, 50));
				_missiles.push_back(new SteadyMissile(player_missile_path, _rect.center().x() - 20,
				                                      _rect.center().y(), 0, -10, 50));
				_missiles.push_back(new SteadyMissile(player_missile_path, _rect.center().x() + 20,
				                                      _rect.center().y(), 0, -10, 50));
			}
			break;
	}
}

void PlayerPlane::Bomb() {
	if (bombs) {
		bombs--;
		for (int i = 0; i < 500; i += 20) {
			_missiles.push_back(
			    new SteadyMissile(player_bomb_path, i, _rect.center().y() - 20, 0, -5, 100));
		}
	}
}

void PlayerPlane::drawMissiles(QPainter& painter) {
	for (_Missile* missile : _missiles) {
		painter.drawPixmap(missile->rect(), missile->picture());
	}
}


void PlayerPlane::drawHP(QPainter& painter) {
	painter.drawRect(QRect(_rect.x(), _rect.y() - 3, _rect.width(), 3));
	painter.fillRect(QRect(_rect.x(), _rect.y() - 3, _rect.width(), 3), Qt::red);
	painter.fillRect(
	    QRect(_rect.x(), _rect.y() - 3, _rect.width() * 1.0 * _health / player_max_health, 3),
	    Qt::green);
}

void PlayerPlane::updateMissiles() {
	for (auto iter = _missiles.begin(); iter != _missiles.end();) {
		if ((*iter)->free()) {
			delete *iter;
			iter = _missiles.erase(iter);
		} else {
			(*iter)->updatePosition();
			++iter;
		}
	}
}

PlayerPlane* PlayerPlane::plane() {
	return _plane;
}

QPolygon PlayerPlane::box() const {
	return QPolygon(QRect(_rect.center(), QSize(1, 1)));
}

void PlayerPlane::hurt(_Plane* __other) {
	_Plane::hurt(__other);
	for (_Missile* missile : _missiles) {
		missile->collide(__other);
	}
}

void PlayerPlane::drawOn(QPainter& painter) {
	painter.drawPixmap(_rect, _picture);
	drawMissiles(painter);
	drawHP(painter);
}
