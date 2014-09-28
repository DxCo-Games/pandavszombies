#include "WeaponSpeedBonus.h"
#include "../../HelloWorldScene.h"

namespace dxco {

WeaponSpeedBonus::WeaponSpeedBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : TimeBonus(model, sprite, animations, WEAPON_SPEED_BONUS_DURATION) {

}

void WeaponSpeedBonus::applyBonus() {
	this->model->vista->updateBonus("bonus/BALAV_activada.png", this->bonusDuration);
	this->model->player->weaponSpeedBonus += WEAPON_SPEED_BONUS_RATIO;
}

void WeaponSpeedBonus::removeBonus() {
	if (this->model->player->weaponSpeedBonus != 1) {
		this->model->player->weaponSpeedBonus -= WEAPON_SPEED_BONUS_RATIO;
	}
}

} /* namespace dxco */
