#include "BulletSpeedBonus.h"

namespace dxco {

BulletSpeedBonus::BulletSpeedBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : TimeBonus(model, sprite, animations, BULLET_SPEED_BONUS_DURATION) {

}

void BulletSpeedBonus::applyBonus() {
	this->model->player->bulletSpeedBonus += 1;
}

void BulletSpeedBonus::removeBonus() {
	this->model->player->bulletSpeedBonus -= 1;
}

} /* namespace dxco */
