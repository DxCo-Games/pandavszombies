#include "FreezeBombBonus.h"

namespace dxco {

FreezeBombBonus::FreezeBombBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : TimeBonus(model, sprite, animations, FREEZE_BOMB_BONUS_DURATION) {
}

void FreezeBombBonus::applyBonus() {
	this->model->freezeBonusActivated = true;

	for (int i = 0; i < this->model->enemies.size(); i++) {
		Enemy* enemy = this->model->enemies[i];
		enemy->freeze();
	}
}

void FreezeBombBonus::removeBonus() {
	this->model->freezeBonusActivated = false;

	for (int i = 0; i < this->model->enemies.size(); i++) {
		Enemy* enemy = this->model->enemies[i];
		enemy->unfreeze();
	}
}

} /* namespace dxco */
