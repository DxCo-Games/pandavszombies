/*
 * BombEnemy.h
 *
 *  Created on: Feb 19, 2015
 *      Author: gsosarolon
 */

#ifndef BOMBENEMY_H_
#define BOMBENEMY_H_

#define ENEMY_EXPLOSION_RANGE 100

#include "Enemy.h"
#include <string>

namespace dxco {

class BombEnemy: public dxco::Enemy {
public:
	BombEnemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int level, std::string type);
	void kill();
};

} /* namespace dxco */
#endif /* BOMBENEMY_H_ */
