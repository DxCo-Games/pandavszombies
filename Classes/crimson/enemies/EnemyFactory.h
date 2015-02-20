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

	void createEnemy(GameModel* model, std::vector<std::string> types);
	void createEnemy(GameModel* model);
	void createEnemy(GameModel* model, std::vector<std::string>types, std::string type, float freq); //create that type with probability, else any other type

	void createBoss(GameModel* model);
	void createBoss(GameModel* model, std::vector<std::string> types);

	void createSuperBoss(GameModel* model, std::vector<std::string> types);

	void createPanda(GameModel* model);
	void createPandaBoss(GameModel* model);

	void createNoobSaibot(GameModel* model);
	void createNoobSaibot(GameModel* model, std::vector<std::string>types, std::string type, float freq);

	void createBombEnemy(GameModel* model);
	void createBombEnemy(GameModel* model, std::vector<std::string>types);

	void createAntEnemy(GameModel* model);
	void createAntEnemy(GameModel* model, std::vector<std::string>types);

	cocos2d::CCSprite* createSpriteInRandomPosition(GameModel* model, std::string texture, int width, int height);

	std::map<int, dxco::Animation*> loadAnimations(GameModel* model, std::string type, float speed);
	std::map<int, dxco::Animation*> pandaAnimations(GameModel* model);
	Enemy* getEnemy(GameModel* model, std::vector<std::string>types);
private:
	void addEnemy(GameModel* model, Enemy* enemy, bool fade = true);
	std::vector<std::string> createTypesVector(bool includeElvis);
	std::vector<std::string> createKillTypesVector(std::vector<std::string>types, std::string type, float freq);
};

} /* namespace dxco */
#endif /* ENEMYFACTORY_H_ */
