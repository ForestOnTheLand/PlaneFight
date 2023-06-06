#include "Generator.h"
#include "EnemyPlane.h"
#include "BattleField.h"
#include "TargetEffect.h"
#include <exception>

static constexpr const char* enemy_plane_path_1 = ":/PlaneFight/img/enemy.png";          // @IMAGE
static constexpr const char* enemy_plane_path_2 = ":/PlaneFight/img/plane/10023.png";    // @IMAGE
static constexpr const char* warning_path = ":/PlaneFight/img/bosswarning.png";          // @IMAGE



namespace Generator {
	using namespace Plane;
	EnemyGenerator* level_0() {
		return new EnemyGenerator(
		    {
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
		            40),
		        new PictureDisplay({{warning_path, battlefield_border.center()}},
                     2),
		        new EnemyClearingPolicy(),
		        new BossGeneratingPolicy(":/PlaneFight/img/boss/Boss_1.png", 50000, 50),
        },
		    true);
	};
	EnemyGenerator* level_1() {
		return new EnemyGenerator({
		    new MessageDisplay(
		        "Mission 1",
		        "And it shall be bestowed upon you,\nthe star which you have longed for.", 3),
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
		         }, {
		             []() {
			             return new EnemyPlane(enemy_plane_path_1, 40, 80, Shoot::Track(),
			                                   Speed::Steady(10, 2), Speed::Steady(100, 2),
			                                   {0.2, 0.2, 0.1, 0.1});
		             },
		             []() {
			             static int timer = 0;
			             if (timer++ <= 150 && timer % 20 == 0) {
				             return 1;
			             } else if (timer <= 1000) {
				             return 0;
			             } else {
				             timer = 0;
				             return 0;
			             }
		             },
		         }, {
		             []() {
			             return new EnemyPlane(enemy_plane_path_1, 40, 80, Shoot::Track(),
			                                   Speed::Steady(10, 2),
			                                   [](int t) {
				                                   return 400 - t * t / 100;
			                                   },
			                                   {0.2, 0.2, 0.1, 0.1});
		             },
		             []() {
			             static int timer = 0;
			             if (timer++ <= 150 && timer % 20 == 0) {
				             return 1;
			             } else if (timer <= 1000) {
				             return 0;
			             } else {
				             timer = 0;
				             return 0;
			             }
		             },
		         }, {
		             []() {
			             return new EnemyPlane(enemy_plane_path_1, 40, 80, Shoot::Track(),
			                                   Speed::Steady(490, -2), Speed::Steady(100, 2),
			                                   {0.2, 0.2, 0.1, 0.1});
		             },
		             []() {
			             static int timer = 0;
			             if (timer++ <= 150 && timer % 20 == 0) {
				             return 1;
			             } else if (timer <= 1000) {
				             return 0;
			             } else {
				             timer = 0;
				             return 0;
			             }
		             },
		         }, {
		             []() {
			             return new EnemyPlane(enemy_plane_path_1, 40, 80, Shoot::Track(),
			                                   Speed::Steady(490, -2),
			                                   [](int t) {
				                                   return 400 - t * t / 100;
			                                   },
			                                   {0.2, 0.2, 0.1, 0.1});
		             },
		             []() {
			             static int timer = 0;
			             if (timer++ <= 150 && timer % 20 == 0) {
				             return 1;
			             } else if (timer <= 1000) {
				             return 0;
			             } else {
				             timer = 0;
				             return 0;
			             }
		             },
		         }},
		        40),
		    new PictureDisplay({{warning_path, battlefield_border.center()}},
                 2),
		    new EnemyClearingPolicy(),
		    new BossGeneratingPolicy(":/PlaneFight/img/boss/Boss_1.png", 40000, 50),
		    new MessageDisplay("Mission Complete!", "However, bigger challenges still lie ahead.",
		                       3),
		});
	};
	EnemyGenerator* level_2() {
		return new EnemyGenerator({
		    new MessageDisplay("Mission 2", "Eclipse first, the rest nowhere.", 3),
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
		    new MessageDisplay("Mission Complete!",
		                       "Bear in mind: Never take your victory for granted.", 3),
		});
	};
	EnemyGenerator* level_3() {
		return new EnemyGenerator({
		    new MessageDisplay("Mission 3", "All tragedy erased, I see only wonders.", 3),
		    new EnemyGeneratingPolicy(
		        {{
		             []() {
			             return new EnemyPlane(enemy_plane_path_2, 150, 20, Shoot::Straight(),
			                                   Speed::RandomX(), Speed::Steady(10, 3),
			                                   {0.2, 0.2, 0.1, 0.1});
		             },
		             Timer::Gap(30),
		         }, {
		             []() {
			             return new EnemyPlane(enemy_plane_path_1, 150, 30, Shoot::ThreeWays(),
			                                   Speed::Steady(random_x()),
			                                   Speed::Stable(30, 3, 200, 500),
			                                   {0.2, 0.2, 0.1, 0.1});
		             },
		             Timer::Gap(30),
		         }},
		        30),
		    new PictureDisplay({{warning_path, battlefield_border.center()}},
                 2),
		    new EnemyClearingPolicy(),
		    new BossGeneratingPolicy(":/PlaneFight/img/boss/Boss_2.png", 100000, 150),
		    new MessageDisplay("Mission Complete!", "Yes, you've conquered all. And then?", 3),
		});
	};

	EnemyGenerator* level(int n) {
		switch (n) {
			case 0: return level_0();
			case 1: return level_1();
			case 2: return level_2();
			case 3: return level_3();
			default: throw std::logic_error(std::string("Invalid level: ") + std::to_string(n));
		}
	}
}    // namespace Generator
