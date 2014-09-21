#include "MovementSpeedBonus.h"
#include "../GameModel.h"
#include "../../dxco/MathUtil.h"

namespace dxco {

MovementSpeedBonus::MovementSpeedBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : Bonus(model, sprite, animations) {
}

void MovementSpeedBonus::applyBonus() {
	CCLOGERROR("APPLY BONUS");
	this->model->player->movementSpeedBonus = MOVEMENT_BONUS_RATE;
	this->dtBonusAcquired = 0;
	this->bonusAcquired = false;
}

void MovementSpeedBonus::removeBonus() {
	Bonus::removeBonus();

	this->model->player->movementSpeedBonus = 1;
}

void MovementSpeedBonus::removeSprite() {
	this->model->mapa->removeChild(this->sprite);
}

void MovementSpeedBonus::update(float dt) {
	float distance = MathUtil::distance(this->getLocation(), this->model->player->getLocation());
	this->dt += dt;

	if (this->bonusAcquired) {
		this->dtBonusAcquired += dt;
	}

	if (this->getSprite()->isVisible()) {
		if (distance < this->getWidth()) {
			this->applyBonus();
			this->getSprite()->setVisible(false);
			this->bonusAcquired = true;
		} else {
			if (this->dt > BONUS_DT) {
				this->removeBonus();
			}
		}
	}

	if (this->bonusAcquired && this->dtBonusAcquired > MOVEMENT_SPEED_BONUS_DURATION) {
		this->removeBonus();
	}
}

} /* namespace dxco */
