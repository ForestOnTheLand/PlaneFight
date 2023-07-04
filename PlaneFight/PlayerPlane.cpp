#include "PlayerPlane.h"
#include "Missile.h"
#include "BattleField.h"

static constexpr const char* player_plane_path = ":/PlaneFight/img/player.png";
static constexpr const char* player_missile_path = ":/PlaneFight/img/missile_0.png";
static constexpr const char* player_hurt_path = ":/PlaneFight/img/player_hurt.png";
static constexpr const char* player_bomb_path = ":/PlaneFight/img/bullet/scale_bullet_red.png";
static constexpr const char* shield_path = ":/PlaneFight/img/effect/shield.png";
static constexpr int max_cool_down = 600;
static constexpr int player_plane_shoot_interval_1 = 20;
static constexpr int player_plane_shoot_interval_2 = 20;
static constexpr int player_plane_shoot_interval_3 = 20;
static constexpr int player_plane_bombs = 3;

PlayerPlane* PlayerPlane::_plane = nullptr;
BattleField* PlayerPlane::_field = nullptr;


PlayerPlane::PlayerPlane(const char* const __image_path, int _bombs)
    : _Plane(__image_path, battlefield_border.center(), player_max_health), bombs(_bombs), score(0),
      power(0) {
	_hurt_image.load(player_hurt_path);
	_shield_picture.load(shield_path);
	_special_missile_icon.load(":/PlaneFight/img/effect/pheonix.png");
}

void PlayerPlane::init(BattleField* b) {
	_field = b;
	if (_plane) {
		delete _plane;
	}
	_plane = new PlayerPlane(player_plane_path, player_plane_bombs);
	_plane->setPosition(battlefield_border.center().x(),
	                    battlefield_border.bottom() - _plane->rect().height());
}


void PlayerPlane::_setPosition(double __x, double __y) {
	_rect.moveCenter({_checked(__x, battlefield_border.left() + _rect.width() / 2,
	                           battlefield_border.right() - _rect.width() / 2),
	                  _checked(__y, battlefield_border.top() + _rect.height() / 2,
	                           battlefield_border.bottom() - _rect.height() / 2)});
}


void PlayerPlane::del() {
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

bool PlayerPlane::Bomb() {
	if (bombs) {
		bombs--;
		for (int i = 0; i < 500; i += 20) {
			_missiles.push_back(
			    new SteadyMissile(player_bomb_path, i, _rect.center().y() - 20, 0, -5, 100));
		}
		return 1;
	}
	return 0;
}

void PlayerPlane::shootUltimate() {
	if (_cool_down_timer <= 0) {
		_special_missile = new SpecialMissile(
		    {
		        ":/PlaneFight/img/effect/phoenix_0.png",
		        ":/PlaneFight/img/effect/phoenix_1.png",
		        ":/PlaneFight/img/effect/phoenix_2.png",
		        ":/PlaneFight/img/effect/phoenix_3.png",
		        ":/PlaneFight/img/effect/phoenix_4.png",
		        ":/PlaneFight/img/effect/phoenix_5.png",
		        ":/PlaneFight/img/effect/phoenix_6.png",
		        ":/PlaneFight/img/effect/phoenix_7.png",
		        ":/PlaneFight/img/effect/phoenix_8.png",
		        ":/PlaneFight/img/effect/phoenix_9.png",
		    },
		    _rect.center().x(), _rect.top(), 3);
		_cool_down_timer = max_cool_down;
	}
}

void PlayerPlane::drawMissiles(QPainter& painter) {
	for (_Missile* missile : _missiles) {
		painter.drawPixmap(missile->rect(), missile->picture(), QRectF());
	}
	if (_special_missile)
		_special_missile->display(painter);
}


void PlayerPlane::drawHP(QPainter& painter) {
	painter.drawRect(QRectF(_rect.x(), _rect.y() - 3, _rect.width(), 3));
	painter.fillRect(QRectF(_rect.x(), _rect.y() - 3, _rect.width(), 3), Qt::red);
	painter.fillRect(
	    QRectF(_rect.x(), _rect.y() - 3, _rect.width() * 1.0 * _health / player_max_health, 3),
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
	if (_cool_down_timer > 0)
		--_cool_down_timer;
	if (_hurt_state > 0)
		_hurt_state--;
	if (buff.shield)
		buff.shield--;
	if (_special_missile) {
		if (_special_missile->free()) {
			delete _special_missile;
			_special_missile = nullptr;
		} else {
			_special_missile->updatePosition();
			_field->enemy_missiles.erase(
			    std::copy_if(_field->enemy_missiles.begin(), _field->enemy_missiles.end(),
			                 _field->enemy_missiles.begin(),
			                 [=](_Missile* missile) -> bool {
				                 return !_special_missile->rect().intersects(missile->rect());
			                 }),
			    _field->enemy_missiles.end());
		}
	}
}

PlayerPlane* PlayerPlane::plane() {
	return _plane;
}

QPolygonF PlayerPlane::box() const {
	return QPolygonF(QRectF(_rect.center(), QSize(1, 1)));
}

void PlayerPlane::attack(_Plane* __other) {
	_Plane::attack(__other);
	for (_Missile* missile : _missiles) {
		missile->collide(__other);
	}
	if (_special_missile)
		_special_missile->collide(__other);
}

void PlayerPlane::drawOn(QPainter& painter) {
	if (_hurt_state > 0) {
		painter.drawPixmap(_rect, _hurt_image, QRectF());

	} else {
		painter.drawPixmap(_rect, _picture, QRectF());
	}
	if (buff.shield) {
		painter.drawPixmap(_rect, _shield_picture, QRectF());
	}
	drawMissiles(painter);
	drawHP(painter);
	drawCD(painter);
}

void PlayerPlane::drawCD(QPainter& painter) {
	painter.save();
	painter.setClipRect(QRect(0, 0, 800, 800));
	painter.drawPixmap(QRect(620, 620, 60, 60), _special_missile_icon);
	if (_cool_down_timer) {
		painter.setBrush(Qt::gray);
		painter.drawPie(QRect(620, 620, 60, 60), 1440, (5760 * _cool_down_timer / max_cool_down));
	}
	painter.setClipRect(battlefield_border);
	painter.restore();
}

void PlayerPlane::changeHealth(int m) {
	if (m < 0) {
		// Attacked
		if (!buff.shield) {
			_health += m;
			_hurt_state = 5;
		}
	} else {
		// Healed
		_health = std::min(_health + m, player_max_health);
	}
}

void PlayerPlane::updatePosition() {}