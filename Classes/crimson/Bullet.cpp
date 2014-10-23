#include "Bullet.h"
#include "enemies/Enemy.h"

namespace dxco {

Bullet::Bullet(cocos2d::CCSprite* sprite, float angle, std::map<int, Animation*>& animations, bool persistent) : Item(sprite, animations) {
	this->angle = angle;
	this->used = false;
	this->persistent = persistent;
}

void Bullet::update(float dt) {
	if (!this->used) {
		Item::update(dt);
		this->move(cos(this->angle) * BULLET_SPEED * dt, sin(this->angle) * BULLET_SPEED * dt);
	}
}


void Bullet::use() {
	if (! this->persistent) {
		this->getSprite()->removeFromParent();
		this->used = true;
	}
}

} /* namespace dxco */
