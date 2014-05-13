#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMY_SPEED 100

#include "cocos2d.h"
#include "../dxco/Item.h"

namespace dxco {

class GameModel;

class Enemy : public Item {
public:
	Enemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);
	void update(float dt);

	GameModel* model;
};

} /* namespace dxco */
#endif /* ENEMY_H_ */
