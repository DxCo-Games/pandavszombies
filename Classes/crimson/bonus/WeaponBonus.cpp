#include "WeaponBonus.h"
#include "../GameModel.h"

namespace dxco {

WeaponBonus::WeaponBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, Player::weapons type) : TimeBonus(model, sprite, animations, WEAPON_BONUS_DURATION) {
	this->type = type;
}

void WeaponBonus::applyBonus(){
	this->model->player->setWeapon(this->type);
}

void WeaponBonus::removeBonus() {
	if (this->model->player->weaponType == this->type) {
		this->model->player->setWeapon(Player::PISTOL);
	}
}

} /* namespace dxco */
