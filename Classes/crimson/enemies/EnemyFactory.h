#ifndef ENEMYFACTORY_H_
#define ENEMYFACTORY_H_

#define MAX_CONCURRENT_ZOMBIES 300

#include "cocos2d.h"

#include "../../dxco/Animation.h"
#include "Enemy.h"

namespace dxco {

class GameModel;

class EnemyFactory {
public:
	EnemyFactory();

	void createEnemy(GameModel* model, std::vector<std::string> types, int extraType);
	void createEnemy(GameModel* model, int extraType=0);
	void createEnemy(GameModel* model, std::vector<std::string>types, std::string type, float freq, int extraType); //create that type with probability, else any other type

	void createBoss(GameModel* model, int extraType=0);
	void createBoss(GameModel* model, std::vector<std::string> types, int extraType);

	void createSuperBoss(GameModel* model, std::vector<std::string> types, int extraType);
	void createPanda(GameModel* model);

	cocos2d::CCSprite* createSpriteInRandomPosition(GameModel* model, std::string texture, int width, int height);

	std::map<int, dxco::Animation*> loadAnimations(GameModel* model, std::string type, float speed);
	std::map<int, dxco::Animation*> pandaAnimations(GameModel* model);
private:
	void addEnemy(GameModel* model, Enemy* enemy);
	std::vector<std::string> createTypesVector(bool includeElvis);
};

} /* namespace dxco */
#endif /* ENEMYFACTORY_H_ */
