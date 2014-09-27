#ifndef ENEMYFACTORY_H_
#define ENEMYFACTORY_H_

#include "cocos2d.h"

#include "../dxco/Animation.h"
#include "Enemy.h"

namespace dxco {

class GameModel;

class EnemyFactory {
public:
	EnemyFactory();

	void createEnemy(GameModel* model);
	void createBoss(GameModel* model);

	cocos2d::CCSprite* createSpriteInRandomPosition(GameModel* model, std::string texture, int width, int height);

	/* We use two batch nodes with different z orders in the map, so we can move the enemies to place them
	 * in front or behind the player based on their y position. */
	cocos2d::CCSpriteBatchNode *enemySpriteSheetFront;
	cocos2d::CCSpriteBatchNode *enemySpriteSheetBack;

	std::map<int, dxco::Animation*> loadAnimations(GameModel* model, std::string type, float frameTime);
private:
	void addEnemy(GameModel* model, Enemy* enemy);
};

} /* namespace dxco */
#endif /* ENEMYFACTORY_H_ */
