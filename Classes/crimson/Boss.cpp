/*
 * Boss.cpp
 *
 *  Created on: May 15, 2014
 *      Author: facundo
 */

#include "Boss.h"

namespace dxco {

Boss::Boss(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) :
	Enemy(model, sprite, animations){
	this-> life = 120;
	this->deadTime = 0;
	this->strength = 50;
}


} /* namespace dxco */
