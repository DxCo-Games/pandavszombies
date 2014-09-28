#include "WeaponBonus.h"
#include "../GameModel.h"
#include "../../HelloWorldScene.h"

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
		this->model->vista->weaponBar->setPercentage(100);
	}
}

void WeaponBonus::update(float dt) {
	TimeBonus::update(dt);
	if (this->bonusAcquired && this->dtBonusAcquired < this->bonusDuration) {
		this->model->vista->weaponBar->setPercentage(100 - this->dtBonusAcquired * 100 / this->bonusDuration);
	}
}

} /* namespace dxco */
