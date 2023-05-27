#include "Generator.h"
#include "EnemyPlane.h"
#include "BattleField.h"

namespace Generator {
	static constexpr const char* enemy_plane_path = ":/PlaneFight/img/enemy.png";    // @IMAGE
	static constexpr const char* warning_path = ":/PlaneFight/img/bosswarning.png";    // @IMAGE
	namespace PolicyFucntion {
		using namespace Plane;
		auto example = [](BattleField* b) {
			static int timer = 0;
			if (++timer >= 60) {
				timer = 0;
				b->_enemies.push_back(new EnemyPlane(enemy_plane_path, 60, 50, Shoot::Straight(),
				                                     Speed::RandomX(), Speed::Steady(10, 3),
				                                     {0.2, 0.2, 0.2}));
				b->_enemies.push_back(new EnemyPlane(
				    enemy_plane_path, 60, 80, Shoot::ThreeWays(), Speed::Steady(random_x()),
				    Speed::Stable(30, 3, 200, 500), {0.2, 0.2, 0.2}));
			}
		};
	}    // namespace PolicyFucntion
}    // namespace Generator

namespace Generator {
	EnemyGenerator* level_1() {
		return new EnemyGenerator({
		    new EnemyGeneratingPolicy(PolicyFucntion::example, 5),
		    new PictureDisplay({{warning_path, battlefield_border.center()}},
             1000),
		    new EnemyClearingPolicy(),
		    new BossGeneratingPolicy(),
		});
	};
}    // namespace Generator
