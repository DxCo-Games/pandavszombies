#include "TimeBonus.h"

#include "../../dxco/MathUtil.h"
#include "../../dxco/VoiceManager.h"
#include "../../HelloWorldScene.h"

namespace dxco {

TimeBonus::TimeBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, float bonusDuration) : Bonus(model, sprite, animations) {
	this->dtBonusAcquired = 0;
	this->bonusAcquired = false;
	this->bonusDuration = bonusDuration;
}

void TimeBonus::update(float dt) {
	//FIXME copy paste Bonus update
	float distance = MathUtil::distance(this->getLocation(), this->model->player->getLocation());
	this->dt += dt;

	if (this->bonusAcquired) {
		this->dtBonusAcquired += dt;
	}

	if (this->getSprite()->isVisible()) {
		if (distance < this->getWidth()) {
			this->applyBonus();
			this->model->vista->playEffect(this->sound);
			this->model->voice->play("voices/groovy.ogg", 0.1);
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
