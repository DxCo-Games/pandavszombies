#include "PuntosBonus.h"

namespace dxco {

PuntosBonus::PuntosBonus(GameModel* model, cocos2d::CCSprite* sprite,
		std::map<int, Animation*>& animations) : Bonus(model, sprite, animations) {
}

void PuntosBonus::applyBonus() {
	this->model->player->score += CANTIDAD_PUNTOS;
}

} /* namespace dxco */
