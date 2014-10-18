#include "Bazooka.h"
#include "GameModel.h"
#include "../dxco/SpriteUtil.h"
#include "BazookaBullet.h"

namespace dxco {

Bazooka::Bazooka(GameModel* model) : Weapon(model){
	this->bulletFrequency = BAZOOKA_FREQUENCY;
}

void Bazooka::shoot() {
	float rotation = this->model->player->getRotation();
	cocos2d::CCPoint location = this->model->player->getLocation();

	this->createBullet(location.x, location.y, 0);
	this->runFlash(location.x, location.y, rotation);
}

void Bazooka::createBulletSprite(float xBulletPosition, float yBulletPosition, float angleBullet, float rotation) {
	//need to tweak the coordinates as the location of the panda is not exactly its center.
	cocos2d::CCSprite* spriteBullet = SpriteUtil::create("bazooka_bullet.png", xBulletPosition - 15 - 10, yBulletPosition - 10 - 20, 20, 20);

	spriteBullet->setRotation(angleBullet + rotation);

	/** degrees to radians */
	float radianAngle = (angleBullet + rotation) / -57.2957795;

	std::map<int, Animation*> animations;
	Bullet* bullet = new BazookaBullet(this->model, spriteBullet, radianAngle, animations);
	this->model->addBullet(bullet);
}

} /* namespace dxco */
