#include "HealthBonus.h"

namespace dxco {

HealthBonus::HealthBonus(GameModel* model, cocos2d::CCSprite* sprite,
		std::map<int, Animation*>& animations) : Bonus(model, sprite, animations) {
}

void HealthBonus::applyBonus(){
	double healAmount = LIFE_AMOUNT_PERCENTAGE * PLAYER_LIFE;
	this->model->player->hurt(-healAmount);
}

} /* namespace dxco */
