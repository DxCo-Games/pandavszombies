#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMY_SPEED 15
#define ENEMY_ANGLE_POSITIONS 8

#include "cocos2d.h"
#include "TopDownItem.h"
#include "Bullet.h"

namespace dxco {

class GameModel;
class Player;

class Enemy : public TopDownItem {
public:
	Enemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);
	void update(float dt);

	bool shoot(Bullet* bullet);
	GameModel* model;
	float life;
	float strength;
	bool burning;
	bool dumb; //me cago en los patrones ;)
	cocos2d::CCPoint* destiny;

	enum estados { ENEMY_STANDING, ENEMY_WALKING };

	void beat(Player* player, float dt);
	void hurt(float value);
	void burn(float dt, cocos2d::CCPoint playerLocation, float distance, float angle);
	virtual bool isActive();
	void setDumbDestiny();

	virtual float getColitionRatio();
};

} /* namespace dxco */
#endif /* ENEMY_H_ */
