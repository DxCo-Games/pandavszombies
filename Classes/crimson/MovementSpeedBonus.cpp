#include "MovementSpeedBonus.h"
#include "GameModel.h"

namespace dxco {

MovementSpeedBonus::MovementSpeedBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : Bonus(model, sprite, animations) {
}

void MovementSpeedBonus::applyBonus(){
	this->model->player->movementSpeedBonus = MOVEMENT_BONUS_RATE;
}

} /* namespace dxco */
