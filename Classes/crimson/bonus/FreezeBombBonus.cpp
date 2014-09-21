#include "FreezeBombBonus.h"

namespace dxco {

FreezeBombBonus::FreezeBombBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : TimeBonus(model, sprite, animations, FREEZE_BOMB_BONUS_DURATION) {
}

void FreezeBombBonus::applyBonus() {
	this->model->freezeBonusActivated = true;
}

void FreezeBombBonus::removeBonus() {
	this->model->freezeBonusActivated = false;
}

} /* namespace dxco */
