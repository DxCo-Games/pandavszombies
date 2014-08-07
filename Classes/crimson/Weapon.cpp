#include "Weapon.h"
#include "GameModel.h"
#include "../dxco/SpriteUtil.h"

namespace dxco {

Weapon::Weapon(GameModel* model) {
	this->model = model;
	this->bulletDt = 0;
	this->bulletFrequency = 0.25;

	this->flashSprite = SpriteUtil::create("disparo/disparo01.png", 0, 0, 50, 50);

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

	//update position depending on player's angle state
	int angleState = this->model->player->getAngleState();
	int width = this->model->player->getWidth();
	int height = this->model->player->getHeight();

	//FIXME calculate this only once.
	//TODO fix rotation to match the end of the weapon
	//TODO fix z level
	//TODO move better along the player?
	switch(angleState) {
	case 0: {
		this->flashSprite->setPositionX(1.2 * width);
		this->flashSprite->setPositionY(0.4 * height);
		this->flashSprite->setRotation(0);
		break;
	}
	case 1: {
		this->flashSprite->setPositionX(1.25 * width);
		this->flashSprite->setPositionY(0.55 * height);
		this->flashSprite->setRotation(-22.5);
		break;
	}
	case 2: {
		this->flashSprite->setPositionX(1.2 * width);
		this->flashSprite->setPositionY(0.7 * height);
		this->flashSprite->setRotation(-45);
		break;
	}
	case 3: {
		this->flashSprite->setPositionX(1 * width);
		this->flashSprite->setPositionY(0.8 * height);
		this->flashSprite->setRotation(-67.5);
		break;
	}
	case 4: {
		//should be under panda
		this->flashSprite->setPositionX(0.75 * width);
		this->flashSprite->setPositionY(0.85 * height);
		this->flashSprite->setRotation(-90);
		break;
	}
	case 5: {
		//don't show it?
		this->flashSprite->setPositionX(0.4 * width);
		this->flashSprite->setPositionY(0.9 * height);
		this->flashSprite->setRotation(-112.5);
		break;
	}
	case 6: {
		this->flashSprite->setPositionX(0.2 * width);
		this->flashSprite->setPositionY(0.8 * height);
		this->flashSprite->setRotation(-135);
		break;
	}
	case 7: {
		//appears again
		this->flashSprite->setPositionX(0);
		this->flashSprite->setPositionY(0.65 * height);
		this->flashSprite->setRotation(-157.5);
		break;
	}
	case 8: {
			this->flashSprite->setPositionX(1.2 * width);
			this->flashSprite->setPositionY(0.5 * height);
			this->flashSprite->setRotation(-180);
			break;
		}
	case 9: {
			this->flashSprite->setPositionX(1.2 * width);
			this->flashSprite->setPositionY(0.5 * height);
			this->flashSprite->setRotation(-202.5);
			break;
		}
	case 10: {
				this->flashSprite->setPositionX(1.2 * width);
				this->flashSprite->setPositionY(0.5 * height);
				this->flashSprite->setRotation(-225);
				break;
			}
	case 11: {
					this->flashSprite->setPositionX(1.2 * width);
					this->flashSprite->setPositionY(0.5 * height);
					this->flashSprite->setRotation(-247.5);
					break;
				}
	case 12: {
					this->flashSprite->setPositionX(1.2 * width);
					this->flashSprite->setPositionY(0.5 * height);
					this->flashSprite->setRotation(-270);
					break;
				}
	case 13: {
					this->flashSprite->setPositionX(1.2 * width);
					this->flashSprite->setPositionY(0.5 * height);
					this->flashSprite->setRotation(-292.5);
					break;
				}
	case 14: {
					this->flashSprite->setPositionX(1.2 * width);
					this->flashSprite->setPositionY(0.5 * height);
					this->flashSprite->setRotation(-315);
					break;
				}
	case 15: {
					this->flashSprite->setPositionX(1.2 * width);
					this->flashSprite->setPositionY(0.5 * height);
					this->flashSprite->setRotation(-337.5);
					break;
				}
	}

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
