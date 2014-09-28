#include "ShieldBonus.h"
#include "HelloWorldScene.h"

namespace dxco {

ShieldBonus::ShieldBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : TimeBonus(model, sprite, animations, SHIELD_BONUS_DURATION) {
}

void ShieldBonus::applyBonus() {
	this->model->vista->updateBonus("bonus/ESCUDO_activado.png", this->bonusDuration);
	this->model->player->shieldActivated = true;
	this->model->vista->bubble->setVisible(true);
}

void ShieldBonus::removeBonus() {
	this->model->player->shieldActivated = false;
	this->model->vista->bubble->setVisible(false);
}

} /* namespace dxco */
