#include "Bullet.h"

namespace dxco {

Bullet::Bullet(cocos2d::CCSprite* sprite, float angle, std::map<int, Animation*>& animations) : Item(sprite, animations) {
	this->angle = angle;
}

void Bullet::update(float dt) {
	Item::update(dt);
	this->move(cos(this->angle) * BULLET_SPEED * dt, sin(this->angle) * BULLET_SPEED * dt);
}

} /* namespace dxco */
