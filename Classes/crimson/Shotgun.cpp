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

	this->createBullet(rotation);
	this->createBullet(rotation + 10);
	this->createBullet(rotation + 5);
	this->createBullet(rotation - 10);
	this->createBullet(rotation - 5);

}

} /* namespace dxco */
