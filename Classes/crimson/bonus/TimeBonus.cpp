#include "TimeBonus.h"

#include "../../dxco/MathUtil.h"

namespace dxco {

TimeBonus::TimeBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, float bonusDuration) : Bonus(model, sprite, animations) {
	this->dtBonusAcquired = 0;
	this->bonusAcquired = false;
	this->bonusDuration = bonusDuration;
}

void TimeBonus::update(float dt) {
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
			this->dtBonusAcquired = 0;
		} else {
			if (this->dt > BONUS_DT) {
				Bonus::removeBonus();
			}
		}
	}

	if (this->bonusAcquired && this->dtBonusAcquired > bonusDuration) {
		Bonus::removeBonus();
		this->removeBonus();
	}
}

} /* namespace dxco */
