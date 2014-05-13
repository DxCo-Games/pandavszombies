#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMY_SPEED 30
#define ENEMY_DEAD_TIME 1

#include "cocos2d.h"
#include "../dxco/Item.h"
#include "Bullet.h"


namespace dxco {

class GameModel;

class Enemy : public Item {
public:
	Enemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);
	void update(float dt);

	bool shoot(Bullet* bullet);
	GameModel* model;
	bool muerto;
	float life;
	float deadTime;
};

} /* namespace dxco */
#endif /* ENEMY_H_ */
