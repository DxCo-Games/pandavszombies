#include "Weapon.h"
#include "GameModel.h"
#include "../dxco/SpriteUtil.h"
#include "HelloWorldScene.h"

namespace dxco {

Weapon::Weapon(GameModel* model) {
	this->model = model;
	this->bulletDt = 0;
	this->bulletFrequency = 0.25;
	this->bullets = -1; //infinite bullets by default

	cocos2d::CCPoint location = model->player->getLocation();
	this->flashSprite = SpriteUtil::create("disparo/disparo01.png", 10, 10, 40, 40);

	std::vector<cocos2d::CCTexture2D*> flashTextures;
	flashTextures.push_back(dxco::SpriteUtil::createTexture("disparo/disparo01.png"));
	flashTextures.push_back(dxco::SpriteUtil::createTexture("disparo/disparo02.png"));
	flashTextures.push_back(dxco::SpriteUtil::createTexture("disparo/disparo03.png"));

	this->flashAnimation = new dxco::Animation(flashTextures, 0.03, false);

	this->model->vista->mapa->addChild(this->flashSprite, 2);
	this->flashSprite->setVisible(false);
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

	//update position depending on player's angle state
	int angleState = this->model->player->getAngleState();

	int screenCenterX = x - 40;
	int screenCenterY = y - 40;

	int playerWidth = 40;
	int playerHeight = 40;
	//FIXME calculate this only once.
	//TODO fix rotation to match the direction of the weapon
	//TODOmorrow

	if (angleState < 8) {
		//put the flash below the panda
		this->flashSprite->setZOrder(model->player->getSprite()->getZOrder() - 2);
		//this->flashSprite->setZOrder(-10);
	} else {
		this->flashSprite->setZOrder(model->player->getSprite()->getZOrder() + 2);
		//this->flashSprite->setZOrder(10);
	}

	float rotationAngle = angleState * -22.5;
	float radianAngle = rotationAngle / -57.2957795;
	this->flashSprite->setVisible(true);
	switch (angleState) {

	case 0: {
		this->flashSprite->setPositionX(
				screenCenterX + 47 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 31 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(0);
		break;
	}
	case 1: {
		this->flashSprite->setPositionX(
				screenCenterX + 54 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 22 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-13);
		break;
	}
	case 2: {
		this->flashSprite->setPositionX(
				screenCenterX + 62 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 16 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-22);
		break;
	}
	case 3: {
		this->flashSprite->setPositionX(
				screenCenterX + 66 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 15 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-35);
		break;
	}
	case 4: {
		this->flashSprite->setPositionX(
				screenCenterX + 57 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 22 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-90);
		break;
	}
	case 5: {
		this->flashSprite->setPositionX(
				screenCenterX + 50 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 25 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-125);
		break;
	}
	case 6: {
		this->flashSprite->setPositionX(
				screenCenterX + 40 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 25 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-150);
		break;
	}
	case 7: {
		this->flashSprite->setPositionX(
				screenCenterX + 38 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 30 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-170);
		break;
	}
	case 8: {
		this->flashSprite->setPositionX(
				screenCenterX + 33 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 39 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-180);
		break;
	}
	case 9: {
		this->flashSprite->setPositionX(
				screenCenterX + 26 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 50 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-185);
		break;
	}
	case 10: {
		this->flashSprite->setPositionX(
				screenCenterX + 18 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 56 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-193);
		break;
	}
	case 11: {
		this->flashSprite->setPositionX(
				screenCenterX + 14 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 55 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-220);
		break;
	}
	case 12: {
		this->flashSprite->setPositionX(
				screenCenterX + 23 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 50 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-270);
		break;
	}
	case 13: {
		this->flashSprite->setPositionX(
				screenCenterX + 31 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 51 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-314);
		break;
	}
	case 14: {
		this->flashSprite->setPositionX(
				screenCenterX + 37 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 49 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-340);
		break;
	}

	case 15: {
		this->flashSprite->setPositionX(
				screenCenterX + 40 + cos(radianAngle) * playerWidth);
		this->flashSprite->setPositionY(
				screenCenterY + 42 + sin(radianAngle) * playerHeight);
		this->flashSprite->setRotation(-355);
		break;
	}
	default: {
		this->flashSprite->setVisible(false);
	}
	}
	this->flashAnimation->restart();
}

void Weapon::createBullet(float x, float y, float rotation) {
	this->bullets -= 1;

	int angleState = this->model->player->getAngleState();

	int screenCenterX = x - 40;
	int screenCenterY = y - 40;

	int playerWidth = 40;
	int playerHeight = 40;

	float xBulletPosition, yBulletPosition, angleBullet;
	//FIXME calculate this only once.

	float rotationAngle = angleState * -22.5;
	float radianAngle = rotationAngle / -57.2957795;

	switch (angleState) {

	case 0: {
		xBulletPosition = screenCenterX + 47 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 30 + sin(radianAngle) * playerHeight;
		angleBullet = 0;
		break;
	}
	case 1: {
		xBulletPosition = screenCenterX + 57 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 17 + sin(radianAngle) * playerHeight;
		angleBullet = -8;
		break;
	}
	case 2: {
		xBulletPosition = screenCenterX + 70 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 10 + sin(radianAngle) * playerHeight;
		angleBullet = -17;
		break;
	}
	case 3: {
		xBulletPosition = screenCenterX + 90 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 15 + sin(radianAngle) * playerHeight;
		angleBullet = -35;
		break;
	}
	case 4: {
		xBulletPosition = screenCenterX + 78 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 17 + sin(radianAngle) * playerHeight;
		angleBullet = -90;
		break;
	}
	case 5: {
		xBulletPosition = screenCenterX + 65 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 25 + sin(radianAngle) * playerHeight;
		angleBullet = -135;
		break;
	}
	case 6: {
		xBulletPosition = screenCenterX + 40 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 25 + sin(radianAngle) * playerHeight;
		angleBullet = -150;
		break;
	}
	case 7: {
		xBulletPosition = screenCenterX + 50 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 26 + sin(radianAngle) * playerHeight;
		angleBullet = -173;
		break;
	}
	case 8: {
		xBulletPosition = screenCenterX + 37 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 37 + sin(radianAngle) * playerHeight;
		angleBullet = -180;
		break;
	}
	case 9: {
		xBulletPosition = screenCenterX + 35 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 45 + sin(radianAngle) * playerHeight;
		angleBullet = -188;
		break;
	}
	case 10: {
		xBulletPosition = screenCenterX + 30 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 50 + sin(radianAngle) * playerHeight;
		angleBullet = -193;
		break;
	}
	case 11: {
		xBulletPosition = screenCenterX + 30 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 55 + sin(radianAngle) * playerHeight;
		angleBullet = -216;
		break;
	}
	case 12: {
		xBulletPosition = screenCenterX + 40 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 50 + sin(radianAngle) * playerHeight;
		angleBullet = -270;
		break;
	}
	case 13: {
		xBulletPosition = screenCenterX + 40 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 59 + sin(radianAngle) * playerHeight;
		angleBullet = -316;
		break;
	}
	case 14: {
		xBulletPosition = screenCenterX + 37 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 51 + sin(radianAngle) * playerHeight;
		angleBullet = -340;
		break;
	}

	case 15: {
		xBulletPosition = screenCenterX + 40 + cos(radianAngle) * playerWidth;
		yBulletPosition = screenCenterY + 40 + sin(radianAngle) * playerHeight;
		angleBullet = -355;
		break;
	}
	}

	//need to tweak the coordinates as the location of the panda is not exactly its center.
	cocos2d::CCSprite* spriteBullet = SpriteUtil::create("bullet.png", xBulletPosition - 2.5 - 20, yBulletPosition - 2.5 - 20, 5, 5);

	spriteBullet->setRotation(angleBullet);

	/** degrees to radians */
	radianAngle = angleBullet / -57.2957795;

	std::map<int, Animation*> animations;
	Bullet* bullet = new Bullet(spriteBullet, radianAngle, animations);
	this->model->addBullet(bullet);
}

} /* namespace dxco */
