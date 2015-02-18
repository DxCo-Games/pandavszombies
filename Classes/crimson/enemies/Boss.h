#ifndef BOSS_H_
#define BOSS_H_

#include "Enemy.h"

namespace dxco {

class GameModel;
class Player;

class Boss: public dxco::Enemy {
public:
	Boss(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int level, std::string type, int extraType);
	virtual float getColitionRatio();
	virtual void kill();
};

} /* namespace dxco */
#endif /* BOSS_H_ */
