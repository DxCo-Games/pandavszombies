#ifndef BULLET_H_
#define BULLET_H_

#define BULLET_SPEED 450

#include "cocos2d.h"
#include "../dxco/Item.h"

namespace dxco {

class Enemy;

class Bullet : public Item {
public:
	Bullet(cocos2d::CCSprite* sprite, float angle, std::map<int, Animation*>& animations, bool persistent = false);
	virtual void update(float dt);

	virtual void use();
	float angle;
	bool used;
	bool persistent;
};

} /* namespace dxco */
#endif /* BULLET_H_ */
