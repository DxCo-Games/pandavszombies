#ifndef BULLET_H_
#define BULLET_H_

#define BULLET_SPEED 300

#include "cocos2d.h"
#include "../dxco/Item.h"

namespace dxco {

class Enemy;

class Bullet : public Item {
public:
	Bullet(cocos2d::CCSprite* sprite, float angle, std::map<int, Animation*>& animations);
	void update(float dt);

	virtual void use();
	virtual float getDamage();
	float angle;
	bool used;
};

} /* namespace dxco */
#endif /* BULLET_H_ */
