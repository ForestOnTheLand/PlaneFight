#include "Generator.h"
#include "EnemyPlane.h"
#include "BattleField.h"
#include "TargetEffect.h"

static constexpr const char* enemy_plane_path = ":/PlaneFight/img/enemy.png";      // @IMAGE
static constexpr const char* warning_path = ":/PlaneFight/img/bosswarning.png";    // @IMAGE



namespace Generator {
	using namespace Plane;
	EnemyGenerator* level_1() {
		return new EnemyGenerator({
		    new MessageDisplay("Mission 1","And it shall be bestowed upon you,\nthe star which you have longed for.", 3),
		    new EnemyGeneratingPolicy(
		        {{
		             []() {
			             return new EnemyPlane(enemy_plane_path, 60, 50, Shoot::Straight(),
			                                   Speed::RandomX(), Speed::Steady(10, 3),
			                                   {0.2, 0.2, 0.2});
		             },
		             Timer::Gap(60),
		         }, {
		             []() {
			             return new EnemyPlane(enemy_plane_path, 60, 80, Shoot::ThreeWays(),
			                                   Speed::Steady(random_x()),
			                                   Speed::Stable(30, 3, 200, 500), {0.2, 0.2, 0.2});
		             },
		             Timer::Gap(60),
		         }},
		        5),
		    new PictureDisplay({{warning_path, battlefield_border.center()}},
                 2),
		    new EnemyClearingPolicy(),
		    new BossGeneratingPolicy(20000, 50),
		    new MessageDisplay("Mission Complete!","However, bigger challenges still lie ahead.", 5),
		});
	};
}    // namespace Generator
