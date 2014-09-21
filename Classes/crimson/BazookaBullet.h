/*
 * BazookaBullet.h
 *
 *  Created on: Sep 21, 2014
 *      Author: gsosarolon
 */

#ifndef BAZOOKABULLET_H_
#define BAZOOKABULLET_H_

#include "Bullet.h"

namespace dxco {

class BazookaBullet: public dxco::Bullet {

	BazookaBullet(cocos2d::CCSprite* sprite, float angle, std::map<int, Animation*>& animations);
	void update(float dt);
};

} /* namespace dxco */
#endif /* BAZOOKABULLET_H_ */
