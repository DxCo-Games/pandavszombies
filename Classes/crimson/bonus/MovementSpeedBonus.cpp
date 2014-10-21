#include "MovementSpeedBonus.h"
#include "../../HelloWorldScene.h"

namespace dxco {

MovementSpeedBonus::MovementSpeedBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : TimeBonus(model, sprite, animations, MOVEMENT_SPEED_BONUS_DURATION) {
}

void MovementSpeedBonus::applyBonus() {
	this->model->player->movementSpeedBonus += MOVEMENT_BONUS_RATE;
	this->model->vista->updateBonus("bonus/VELOCIDAD_activado.png", this->bonusDuration);
}

void MovementSpeedBonus::removeBonus() {
	if (this->model->player->movementSpeedBonus != 1) {
		this->model->player->movementSpeedBonus -= MOVEMENT_BONUS_RATE;
	}
}

} /* namespace dxco */
