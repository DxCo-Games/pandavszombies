#include "WeaponBonus.h"
#include "../GameModel.h"
#include "../../HelloWorldScene.h"

namespace dxco {

WeaponBonus::WeaponBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, Player::weapons type) : TimeBonus(model, sprite, animations, WEAPON_BONUS_DURATION) {
	this->type = type;
	this->sound = "sounds/loadgun.ogg";
}

void WeaponBonus::applyBonus() {

	this->model->player->weaponBonus = this;

	this->model->player->setWeapon(this->type);
	this->model->vista->weaponBar->setPercentage(100);

	if (this->type == Player::BAZOOKA) {
		this->model->vista->playEffect("voices/friend.ogg", 50);
	}
}

void WeaponBonus::removeBonus() {
	if (this->model->player->weaponBonus == this) {
		this->model->player->weaponBonus = NULL;

		if (this->model->player->weaponType == this->type) {
			this->model->player->setWeapon(Player::PISTOL);
			this->model->vista->weaponBar->setPercentage(100);
		}
	}
}

void WeaponBonus::update(float dt) {
	TimeBonus::update(dt);

	/* Only the last weapon should update the weaponBar */
	if (this->bonusAcquired && this->dtBonusAcquired < this->bonusDuration && this->model->player->weaponBonus == this) {
		this->model->vista->weaponBar->setPercentage(100 - this->dtBonusAcquired * 100 / this->bonusDuration);
	}
}

} /* namespace dxco */
