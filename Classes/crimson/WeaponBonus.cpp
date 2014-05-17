#include "WeaponBonus.h"
#include "GameModel.h"

namespace dxco {

WeaponBonus::WeaponBonus(GameModel* model, cocos2d::CCSprite* sprite,
		std::map<int, Animation*>& animations, Player::weapons type) : Bonus(model, sprite, animations) {
	this->type = type;
}

void WeaponBonus::applyBonus(){
	this->model->player->setWeapon(this->type);
}

} /* namespace dxco */
