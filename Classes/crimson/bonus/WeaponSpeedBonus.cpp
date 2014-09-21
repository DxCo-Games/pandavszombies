#include "WeaponSpeedBonus.h"

namespace dxco {

WeaponSpeedBonus::WeaponSpeedBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : TimeBonus(model, sprite, animations, WEAPON_SPEED_BONUS_DURATION) {

}

void WeaponSpeedBonus::applyBonus() {
	this->model->player->bulletSpeedBonus += 1;
}

void WeaponSpeedBonus::removeBonus() {
	this->model->player->bulletSpeedBonus -= 1;
}

} /* namespace dxco */
