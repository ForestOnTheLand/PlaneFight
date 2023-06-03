#include "Generator.h"
#include "EnemyPlane.h"
#include "BattleField.h"
#include "TargetEffect.h"

static constexpr const char* enemy_plane_path_1 = ":/PlaneFight/img/enemy.png";          // @IMAGE
static constexpr const char* enemy_plane_path_2 = ":/PlaneFight/img/plane/10023.png";    // @IMAGE
static constexpr const char* warning_path = ":/PlaneFight/img/bosswarning.png";          // @IMAGE



namespace Generator {
	using namespace Plane;

	EnemyGenerator* level_1() {
		return new EnemyGenerator({
		    new MessageDisplay("Mission 1", 3),
		    new EnemyGeneratingPolicy(
		        {{
		             []() {
			             return new EnemyPlane(enemy_plane_path_2, 60, 50, Shoot::Straight(),
			                                   Speed::RandomX(), Speed::Steady(10, 3),
			                                   {0.2, 0.2, 0.1, 0.1});
		             },
		             Timer::Gap(60),
		         }, {
		             []() {
			             return new EnemyPlane(enemy_plane_path_1, 60, 80, Shoot::ThreeWays(),
			                                   Speed::Steady(random_x()),
			                                   Speed::Stable(30, 3, 200, 500),
			                                   {0.2, 0.2, 0.1, 0.1});
		             },
		             Timer::Gap(60),
		         }},
		        30),
		    new PictureDisplay({{warning_path, battlefield_border.center()}},
                 2),
		    new EnemyClearingPolicy(),
		    new BossGeneratingPolicy(":/PlaneFight/img/boss/Boss_1.png", 50000, 50),
		    new MessageDisplay("Mission Complete!", 5),
		});
	};
	EnemyGenerator* level_2() {
		return new EnemyGenerator({
		    new MessageDisplay("Mission 2", 3),
		    new EnemyGeneratingPolicy(
		        {{
		             []() {
			             return new EnemyPlane(enemy_plane_path_2, 120, 30, Shoot::Straight(),
			                                   Speed::RandomX(), Speed::Steady(10, 3),
			                                   {0.2, 0.2, 0.1, 0.1});
		             },
		             Timer::Gap(60),
		         }, {
		             []() {
			             return new EnemyPlane(enemy_plane_path_1, 120, 40, Shoot::ThreeWays(),
			                                   Speed::Steady(random_x()),
			                                   Speed::Stable(30, 3, 200, 500),
			                                   {0.2, 0.2, 0.1, 0.1});
		             },
		             Timer::Gap(60),
		         }},
		        30),
		    new PictureDisplay({{warning_path, battlefield_border.center()}},
                 2),
		    new EnemyClearingPolicy(),
		    new BossGeneratingPolicy(":/PlaneFight/img/boss/Boss_2.png", 60000, 80),
		    new MessageDisplay("Mission Complete!", 5),
		});
	};
	EnemyGenerator* level_3() {
		return new EnemyGenerator({
		    new MessageDisplay("Mission 3", 3),
		    new EnemyGeneratingPolicy(
		        {{
		             []() {
			             return new EnemyPlane(enemy_plane_path_2, 200, 20, Shoot::Straight(),
			                                   Speed::RandomX(), Speed::Steady(10, 3),
			                                   {0.2, 0.2, 0.1, 0.1});
		             },
		             Timer::Gap(60),
		         }, {
		             []() {
			             return new EnemyPlane(enemy_plane_path_1, 300, 30, Shoot::ThreeWays(),
			                                   Speed::Steady(random_x()),
			                                   Speed::Stable(30, 3, 200, 500),
			                                   {0.2, 0.2, 0.1, 0.1});
		             },
		             Timer::Gap(60),
		         }},
		        30),
		    new PictureDisplay({{warning_path, battlefield_border.center()}},
                 2),
		    new EnemyClearingPolicy(),
		    new BossGeneratingPolicy(":/PlaneFight/img/boss/Boss_2.png", 100000, 150),
		    new MessageDisplay("Mission Complete!", 5),
		});
	};

	EnemyGenerator* level(int n) {
		switch (n) {
			case 1: return level_1();
			case 2: return level_2();
			case 3: return level_3();
			default: return level_1();
		}
	}
}    // namespace Generator
