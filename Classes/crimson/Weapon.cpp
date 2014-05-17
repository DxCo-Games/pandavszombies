#include "Weapon.h"
#include "GameModel.h"
#include "../dxco/SpriteUtil.h"

namespace dxco {

Weapon::Weapon(GameModel* model) {
	this->model = model;
	this->bulletDt = 0;
	this->bulletFrequency = 0.25;
}

void Weapon::update(float dt) {
	this->bulletDt += dt;

	if (this->bulletDt > this->bulletFrequency) {
		this->shoot();
		this->bulletDt = 0;
	}
}

void Weapon::shoot() {
	float rotation = this->model->player->getSprite()->getRotation();
	this->createBullet(rotation);
}

void Weapon::createBullet(float rotation) {
	cocos2d::CCPoint location = this->model->player->getLocation();

	cocos2d::CCSprite* spriteBullet = SpriteUtil::create("bullet.png", location.x, location.y, 5, 5);

	spriteBullet->setRotation(rotation);

	/** degrees to radians */
	float angle = -rotation / 57.2957795;

	//fix position of the bullet to actually come out the weapon. the last number fixes sprites nonesense
	float R = 18;
	SpriteUtil::moveTo(spriteBullet, location.x + R * cos(angle), location.y + R * sin(angle) - 16);

	std::map<int, Animation*> animations;
	Bullet* bullet = new Bullet(spriteBullet, angle, animations);
	this->model->addBullet(bullet);
}

} /* namespace dxco */
