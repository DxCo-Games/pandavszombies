#include "FreezeBombBonus.h"
#include "../../HelloWorldScene.h"

namespace dxco {

FreezeBombBonus::FreezeBombBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : TimeBonus(model, sprite, animations, FREEZE_BOMB_BONUS_DURATION) {
}

void FreezeBombBonus::applyBonus() {
	this->model->freezeBonusActivated += 1;
	this->model->vista->updateBonus("bonus/CONGELAR_activado.png", this->bonusDuration);

	if (this->model->freezeBonusActivated == 1) {
		for (int i = 0; i < this->model->enemies.size(); i++) {
			Enemy* enemy = this->model->enemies[i];

			if (enemy->isActive()) { // Only freeze enemies that are not dead
				enemy->freeze();
			}
		}
	}
}

void FreezeBombBonus::removeBonus() {
	this->model->freezeBonusActivated -= 1;

	if (this->model->freezeBonusActivated == 0) {
		for (int i = 0; i < this->model->enemies.size(); i++) {
			Enemy* enemy = this->model->enemies[i];

			if (enemy->isActive()) {
				enemy->unfreeze();
			}
		}
	}
}

} /* namespace dxco */
