#include "Bullet.h"
#include "Enemy.h"

namespace dxco {

Bullet::Bullet(cocos2d::CCSprite* sprite, float angle, std::map<int, Animation*>& animations) : Item(sprite, animations) {
	this->angle = angle;
	this->used = false;
}

void Bullet::update(float dt) {
	if (!this->used) {
		Item::update(dt);
		this->move(cos(this->angle) * BULLET_SPEED * dt, sin(this->angle) * BULLET_SPEED * dt);
	}
}


void Bullet::use() {
	this->getSprite()->removeFromParent();
	this->used = true;
}

float Bullet::getDamage() {
	return 10;
}

} /* namespace dxco */
