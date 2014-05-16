/*
 * HealthBonus.cpp
 *
 *  Created on: May 16, 2014
 *      Author: facundo
 */

#include "HealthBonus.h"
#include "GameModel.h"

namespace dxco {

HealthBonus::HealthBonus(GameModel* model, cocos2d::CCSprite* sprite,
		std::map<int, Animation*>& animations) : Bonus(model, sprite, animations) {
}

void HealthBonus::applyBonus(){
	this->model->player->hurt(-LIFE_AMOUNT);
}

} /* namespace dxco */
