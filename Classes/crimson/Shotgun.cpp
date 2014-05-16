#include "Shotgun.h"
#include "cocos2d.h"
#include "Bullet.h"
#include "../dxco/SpriteUtil.h"
#include "GameModel.h"


namespace dxco {

Shotgun::Shotgun(GameModel* model): Weapon(model) {
	this->bulletFrequency = 0.75;
}

void Shotgun::shoot() {
	float rotation = this->model->player->getSprite()->getRotation();

	this->createBullet(rotation);
	this->createBullet(rotation + rotation * 0.05);
	this->createBullet(rotation + rotation * 0.1);
	this->createBullet(rotation - rotation * 0.05);
	this->createBullet(rotation - rotation * 0.1);

}

} /* namespace dxco */
