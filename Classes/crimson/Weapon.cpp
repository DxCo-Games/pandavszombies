#include "Weapon.h"
#include "GameModel.h"
#include "../dxco/SpriteUtil.h"

namespace dxco {

Weapon::Weapon(GameModel* model) {
	this->model = model;
	this->bulletDt = 0;
	this->bulletFrequency = 0.25;

	this->flashSprite = SpriteUtil::create("disparo/disparo01.png", 0, 0, 30, 30);

	std::vector<cocos2d::CCTexture2D*> flashTextures;
	flashTextures.push_back(dxco::SpriteUtil::createTexture("disparo/disparo01.png"));
	flashTextures.push_back(dxco::SpriteUtil::createTexture("disparo/disparo02.png"));
	flashTextures.push_back(dxco::SpriteUtil::createTexture("disparo/disparo03.png"));
	this-> flashAnimation = new dxco::Animation(flashTextures, 0.04, false);

	model->player->getSprite()->addChild(this->flashSprite);
}

void Weapon::update(float dt) {

	this->flashAnimation->update(this->flashSprite, dt);
	if (this->flashAnimation->finished) {
		this->flashSprite->setVisible(false);
	}

	this->bulletDt += dt;

	if (this->bulletDt > this->bulletFrequency) {
		this->shoot();
		this->bulletDt = 0;
	}

}

void Weapon::shoot() {
	float rotation = this->model->player->getRotation();
	cocos2d::CCPoint location = this->model->player->getLocation();

	this->createBullet(location.x, location.y, rotation);
	this->runFlash(location.x, location.y, rotation);
}

void Weapon::runFlash(float x, float y, float rotation) {
	this->flashSprite->setRotation(rotation);
//	this->flashSprite->setPositionX(x);
//	this->flashSprite->setPositionY(y);
	this->flashSprite->setVisible(true);
	this->flashAnimation->restart();
}

void Weapon::createBullet(float x, float y, float rotation) {

	cocos2d::CCSprite* spriteBullet = SpriteUtil::create("bullet.png", x, y, 5, 5);

	spriteBullet->setRotation(rotation);

	/** degrees to radians */
	float angle = -rotation / 57.2957795;

	//fix position of the bullet to actually come out the weapon. the last number fixes sprites nonesense
	float R = 18;
	SpriteUtil::moveTo(spriteBullet, x + R * cos(angle), y + R * sin(angle) - 16);

	std::map<int, Animation*> animations;
	Bullet* bullet = new Bullet(spriteBullet, angle, animations);
	this->model->addBullet(bullet);
}

} /* namespace dxco */
