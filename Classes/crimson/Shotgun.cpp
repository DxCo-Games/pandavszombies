#include "Shotgun.h"
#include "cocos2d.h"
#include "Bullet.h"
#include "../dxco/SpriteUtil.h"
#include "GameModel.h"
#include "../HelloWorldScene.h"

namespace dxco {

Shotgun::Shotgun(GameModel* model): Weapon(model) {
	this->bulletFrequency = 0.8;
	this->sound = "sounds/shotgun2.ogg";
}

void Shotgun::shoot() {
	float rotation = this->model->player->getRotation();
	cocos2d::CCPoint location = this->model->player->getLocation();

	this->createBullet(location.x, location.y, 0);
	this->createBullet(location.x, location.y, 2.5);
	this->createBullet(location.x, location.y, 5);
	this->createBullet(location.x, location.y, 7.5);
	this->createBullet(location.x, location.y, -2.5);
	this->createBullet(location.x, location.y, -5);
	this->createBullet(location.x, location.y, -7.5);

	this->runFlash(location.x, location.y, rotation);
}

} /* namespace dxco */
