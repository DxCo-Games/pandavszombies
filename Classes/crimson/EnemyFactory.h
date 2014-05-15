#ifndef ENEMYFACTORY_H_
#define ENEMYFACTORY_H_

#define ENEMY_DT 0.75
#define BOSS_DT 30

#include "cocos2d.h"

namespace dxco {

class GameModel;

class EnemyFactory {
public:
	EnemyFactory();
	void update(GameModel* model, float dt);

	void createEnemy(GameModel* model);
	void createBoss(GameModel* model);

	cocos2d::CCSprite* getRandomSprite(std::string texture, int width, int height);

	float enemyDt;
	float bossDt;
};

} /* namespace dxco */
#endif /* ENEMYFACTORY_H_ */
