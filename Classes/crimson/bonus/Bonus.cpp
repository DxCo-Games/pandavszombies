#include "Bonus.h"
#include "../GameModel.h"
#include "../../HelloWorldScene.h"
#include "../../dxco/MathUtil.h"
#include "../../dxco/VoiceManager.h"
#include <algorithm>

namespace dxco {

Bonus::Bonus(GameModel* model, cocos2d::CCSprite* sprite,
		std::map<int, Animation*>& animations) :
		Item(sprite, animations) {
	this->model = model;
	this->dt = 0;
	this->sound = "sounds/bonus.ogg";

	sprite->runAction(cocos2d::CCFadeOut::create(BONUS_DT + 0.1));
}

void Bonus::update(float dt) {
	float distance = MathUtil::distance(this->getLocation(), this->model->player->getLocation());
	if (distance < this->getWidth()) {
		this->applyBonus();
		this->model->vista->playEffect(this->sound);
		this->model->voice->play("voices/groovy.ogg", 0.1);
		this->removeBonus();
	} else {
		this->dt += dt;
		if (this->dt > BONUS_DT) {
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
