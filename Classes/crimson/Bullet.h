#ifndef BULLET_H_
#define BULLET_H_

#define BULLET_SPEED 250

#include "cocos2d.h"
#include "../dxco/Item.h"
namespace dxco {

class Bullet : public Item {
public:
	Bullet(cocos2d::CCSprite* sprite, float angle, std::map<int, Animation*>& animations);
	void update(float dt);
	float angle;
};

} /* namespace dxco */
#endif /* BULLET_H_ */
