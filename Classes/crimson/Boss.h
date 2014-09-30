#ifndef BOSS_H_
#define BOSS_H_

#include "Enemy.h"

namespace dxco {

class GameModel;
class Player;

class Boss: public dxco::Enemy {
public:
	Boss(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, float speed);
	virtual float getColitionRatio();
};

} /* namespace dxco */
#endif /* BOSS_H_ */
