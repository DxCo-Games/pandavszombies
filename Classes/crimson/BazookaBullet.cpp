/*
 * BazookaBullet.cpp
 *
 *  Created on: Sep 21, 2014
 *      Author: gsosarolon
 */

#include "BazookaBullet.h"

namespace dxco {

BazookaBullet::BazookaBullet(cocos2d::CCSprite* sprite, float angle, std::map<int, Animation*>& animations) : Bullet(sprite, angle, animations) {

}

void BazookaBullet::update(float dt) {
	if (!this->used) {
		Item::update(dt);
		this->move(cos(this->angle) * BULLET_SPEED / 4 * dt, sin(this->angle) * BULLET_SPEED / 4 * dt);
	}
}




} /* namespace dxco */
