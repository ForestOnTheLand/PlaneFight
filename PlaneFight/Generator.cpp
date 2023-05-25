#include "Generator.h"
#include "EnemyPlane.h"
#include "BattleField.h"

namespace Generator {
	static constexpr const char* enemy_plane_path = ":/PlaneFight/img/enemy.png";    // @IMAGE
	namespace PolicyFucntion {
		auto example = [](BattleField* b) {
			static int timer = 0;
			if (++timer >= 60) {
				timer = 0;
				EnemyPlane* enemy = new TrivialEnemyPlane(enemy_plane_path, 60);
				enemy->setPosition(randint(battlefield_border.left(), battlefield_border.right()),
				                   10);
				b->_enemies.push_back(enemy);
				EnemyPlane* enemy1 = new StableEnemyPlane(enemy_plane_path, 60, 200);
				enemy1->setPosition(
				    randint(battlefield_border.left() + 100, battlefield_border.right() - 100), 10);
				b->_enemies.push_back(enemy1);
			}
		};
	}    // namespace PolicyFucntion
}    // namespace Generator

namespace Generator {
	EnemyGenerator* example_generator(new EnemyGenerator({
	    new EnemyGeneratingPolicy(PolicyFucntion::example, 5000),
	}));
	EnemyGenerator* level_1(new EnemyGenerator({
	    new EnemyGeneratingPolicy(PolicyFucntion::example, 30),
	    new EnemyClearingPolicy(),
	    new BossGeneratingPolicy(),
	}));
}    // namespace Generator
