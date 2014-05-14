#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMY_SPEED 15
#define ENEMY_DEAD_TIME 180

#include "cocos2d.h"
#include "../dxco/Item.h"
#include "Bullet.h"

namespace dxco {

class GameModel;
class Player;

class Enemy : public Item {
public:
	Enemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);
	void update(float dt);

	bool shoot(Bullet* bullet);
	GameModel* model;
	bool muerto;
	float life;
	float deadTime;

	enum estados { ENEMY_WALKING, ENEMY_BEATING, ENEMY_DEAD };

	void beat(Player* player);
	void hurt(float value);
	virtual bool isActive();

	virtual float getWidth();
};

} /* namespace dxco */
#endif /* ENEMY_H_ */
