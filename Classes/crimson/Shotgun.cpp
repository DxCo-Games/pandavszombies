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
	float rotation = this->model->player->getRotation();
	cocos2d::CCPoint location = this->model->player->getLocation();

	this->createBullet(location.x, location.y, rotation);
	this->createBullet(location.x, location.y, rotation + 10);
	this->createBullet(location.x, location.y, rotation + 5);
	this->createBullet(location.x, location.y, rotation - 10);
	this->createBullet(location.x, location.y, rotation - 5);

	this->runFlash(location.x, location.y, rotation);
}

} /* namespace dxco */
