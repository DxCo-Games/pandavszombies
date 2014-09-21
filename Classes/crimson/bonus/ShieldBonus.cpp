#include "ShieldBonus.h"

namespace dxco {

ShieldBonus::ShieldBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : TimeBonus(model, sprite, animations, SHIELD_BONUS_DURATION) {
}

void ShieldBonus::applyBonus() {
	this->model->player->shieldActivated = true;
}

void ShieldBonus::removeBonus() {
	this->model->player->shieldActivated = false;
}

} /* namespace dxco */
