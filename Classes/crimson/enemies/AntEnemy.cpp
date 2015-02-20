/*
 * AntEnemy.cpp
 *
 *  Created on: Feb 20, 2015
 *      Author: gsosarolon
 */

#include "/Users/gsosarolon/Documents/workspace/cocos2d-x/samples/Cpp/crimson/Classes/crimson/enemies/AntEnemy.h"

namespace dxco {

AntEnemy::AntEnemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int level, std::string type): Enemy(model, sprite, animations, level, type), Item(sprite, animations) {
	this->score = 1;
	this->life = 1;
	this->strength = 1;
}

float AntEnemy::getWidth() {
	// para mejorar colisiones
	return Item::getWidth() * 3;
}

} /* namespace dxco */
