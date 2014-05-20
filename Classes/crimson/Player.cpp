#include "Player.h"
#include "Bullet.h"
#include "GameModel.h"
#include "Weapon.h"
#include "Shotgun.h"
#include "SMG.h"
#include "../HelloWorldScene.h"
#include "../dxco/SpriteUtil.h"

namespace dxco {

Player::Player(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : Item(sprite, animations) {
	this->state = QUIETO;
	this->life = PLAYER_LIFE;
	this->moving = false;

	cocos2d::CCSize size =
			cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	this->width = size.width * 2;
	this->height = size.height * 2;
}

int Player::getState() {
	return this->state;
}

void Player::hurt(float damage) {
	this->life -= damage;
	if(damage > 0) {
		this->model->damage = true;
	}

	if (this->life > PLAYER_LIFE) {
		this->life = PLAYER_LIFE;
	}
}


void Player::update(float dt) {
	//FIXME this line is overriding the sprite of the weapon
	//	Item::update(dt);

	if (this->moving) {
		cocos2d::CCPoint position = this->getLocation();

		float x = position.x;
		float y = position.y;

		float deltaX = cos(this->angle) * PLAYER_SPEED * dt;
		float deltaY = sin(this->angle) * PLAYER_SPEED * dt;

		float finalX = x + deltaX;
		float finalY = y + deltaY;

		if (finalX > 0 && finalX < this->width && finalY > 0
				&& finalY < this->height) {
			this->model->mapa->move(-deltaX, -deltaY);
		}
	}
}

bool Player::isActive() {
	return this->life > 0;
}

void Player::setWeapon(weapons type) {
	//TODO change sprites
	switch(type) {
	case SHOTGUN: {
		this->weapon = new Shotgun(this->model);
		SpriteUtil::setTexture(this->sprite, "citizenplayershotgun.png");
		break;
	}
	case SMG_: {
		this->weapon = new SMG(this->model);
		SpriteUtil::setTexture(this->sprite, "citizenplayer_uzi.png");
		break;
	}
	default:{
		this->weapon = new Weapon(this->model);
		SpriteUtil::setTexture(this->sprite, "citizenplayer_handgun.png");
		break;
	}
	}
}


cocos2d::CCPoint Player::getLocation() {
	cocos2d::CCPoint location = Item::getLocation();
	location.setPoint(location.x - this->model->vista->mapa->getPositionX(),
			location.y - this->model->vista->mapa->getPositionY());

	return location;
}

} /* namespace dxco */
