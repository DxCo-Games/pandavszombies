#ifndef GAMEFACTORY_H_
#define GAMEFACTORY_H_

#include "Enemy.h"
namespace dxco {

class GameModel;

class GameFactory {
public:
	static Enemy* createEnemy(GameModel* model);
};

} /* namespace dxco */
#endif /* GAMEFACTORY_H_ */
