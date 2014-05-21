/*
 * Bonus.cpp
 *
 *  Created on: May 16, 2014
 *      Author: facundo
 */

#include "Bonus.h"
#include "GameModel.h"
#include <algorithm>

namespace dxco {

Bonus::Bonus(GameModel* model, cocos2d::CCSprite* sprite,
		std::map<int, Animation*>& animations) :
		Item(sprite, animations) {
	this->model = model;
	this->dt = 0;
}

void Bonus::update(float dt) {
	if (this->collides(this->model->player)) {
		this->applyBonus();
		this->removeBonus();
	} else {
		this->dt += dt;
		if (this->dt > WEAPON_DT) {
			this->removeBonus();
		}
	}
}

void Bonus::removeBonus() {
	this->model->mapa->removeChild(this->sprite);
	//this removes the bonus. cpp, don't ask.
	this->model->bonuses.erase(std::remove(this->model->bonuses.begin(), this->model->bonuses.end(), this),
			this->model->bonuses.end());
}

} /* namespace dxco */
