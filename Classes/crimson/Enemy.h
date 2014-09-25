#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMY_ANGLE_POSITIONS 8
#define ENEMY_DEFAULT_SPEED 30
#define ENEMY_WANDER_SPEED 20
#define ENEMY_WANDER_RANGE 200
#define ENEMY_SEEK_RANGE 80
#define ENEMY_ARRIVE_RANGE 30
#define ENEMY_BLOOD_DURATION 5

#include "cocos2d.h"
#include "../dxco/TopDownItem.h"
#include "../dxco/SteeringBehaviorItem.h"
#include "Bullet.h"
#include "../dxco/Action.h"

namespace dxco {

class GameModel;
class Player;

class Enemy : public TopDownItem, public SteeringBehaviorItem {
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
	float bloodDt;

	int score;

	enum estados { ENEMY_STANDING, ENEMY_WALKING, ENEMY_DEAD };

	void beat(Player* player, float dt);
	void hurt(float value);
	void burn(float dt, cocos2d::CCPoint playerLocation, float distance, float angle);
	virtual bool isActive();
	virtual float getColitionRatio();
	void setNewWanderTarget();
	float getWanderSpeed();
	void fixZOrder(float playerY);

	void freeze();
	void unfreeze();

	virtual void stand(float dt, cocos2d::CCPoint target);

	cocos2d::CCAction* action;
};

} /* namespace dxco */
#endif /* ENEMY_H_ */
