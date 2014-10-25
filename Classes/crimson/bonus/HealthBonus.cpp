#include "HealthBonus.h"
#include "../GameProperties.h"

namespace dxco {

HealthBonus::HealthBonus(GameModel* model, cocos2d::CCSprite* sprite,
		std::map<int, Animation*>& animations) : Bonus(model, sprite, animations) {
}

void HealthBonus::applyBonus(){
	double healAmount = LIFE_AMOUNT_PERCENTAGE * this->model->prop->get("player.life");
	this->model->player->hurt(-healAmount);
}

} /* namespace dxco */
