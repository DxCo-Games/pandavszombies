#ifndef ENEMYFACTORY_H_
#define ENEMYFACTORY_H_

#include "cocos2d.h"

#include "../../dxco/Animation.h"
#include "Enemy.h"

namespace dxco {

class GameModel;

class EnemyFactory {
public:
	EnemyFactory();

	void createEnemy(GameModel* model, std::vector<std::string> types);
	void createEnemy(GameModel* model);
	void createEnemy(GameModel* model, std::string type, float freq); //create that type with probability, else any other type
	void createBoss(GameModel* model);

	cocos2d::CCSprite* createSpriteInRandomPosition(GameModel* model, std::string texture, int width, int height);

	std::map<int, dxco::Animation*> loadAnimations(GameModel* model, std::string type, float speed);
private:
	void addEnemy(GameModel* model, Enemy* enemy);
};

} /* namespace dxco */
#endif /* ENEMYFACTORY_H_ */
