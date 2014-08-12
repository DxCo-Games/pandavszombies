#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMY_ANGLE_POSITIONS 8

#include "cocos2d.h"
#include "TopDownItem.h"
#include "Bullet.h"
#include "../dxco/Action.h"

namespace dxco {

class GameModel;
class Player;

class Enemy : public TopDownItem {
public:
	Enemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);
	void update(float dt);

	static int ENEMY_SPEED;

	bool shoot(Bullet* bullet);
	GameModel* model;
	float life;
	float strength;
	bool burning;
	bool dead;

	int score;

	cocos2d::CCPoint* destiny;

	enum estados { ENEMY_STANDING, ENEMY_WALKING };

	void beat(Player* player, float dt);
	void hurt(float value);
	void burn(float dt, cocos2d::CCPoint playerLocation, float distance, float angle);
	virtual bool isActive();
	virtual float getColitionRatio();
	void setDumbDestiny();

	cocos2d::CCAction* action;
};

} /* namespace dxco */
#endif /* ENEMY_H_ */
