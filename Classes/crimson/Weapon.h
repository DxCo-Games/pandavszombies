#ifndef WEAPON_H_
#define WEAPON_H_

#include "cocos2d.h"
#include "../dxco/Animation.h"

namespace dxco {

class GameModel;

class Weapon {

public:
	Weapon(GameModel* model);

	virtual void update(float dt);
	virtual void shoot();
	void runFlash(float x, float y, float rotation);
	void updateFlash(float x, float y, float rotation);
	void createBullet(float x, float y, float rotation);

	virtual void createBulletSprite(float x, float y, float angleBullet, float rotation);
	int bullets;
	GameModel* model;
	float bulletDt;
	float bulletFrequency;

	cocos2d::CCSprite *flashSprite;
	Animation *flashAnimation;
};


} /* namespace dxco */

#endif /* WEAPON_H_ */
