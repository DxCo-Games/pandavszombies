#ifndef ANTENEMY_H_
#define ANTENEMY_H_

#include "Enemy.h"

namespace dxco {

class AntEnemy: public Enemy {
public:
	AntEnemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int level, std::string type);
	float getWidth();
};

} /* namespace dxco */
#endif /* ANTENEMY_H_ */
