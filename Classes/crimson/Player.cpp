#include "Player.h"
#include "Bullet.h"
#include "GameModel.h"
#include "Weapon.h"
#include "Shotgun.h"
#include "SMG.h"
#include "../dxco/SpriteUtil.h"

namespace dxco {

Player::Player(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : Item(sprite, animations) {
	this->state = QUIETO;
	this->life = PLAYER_LIFE;
}

int Player::getState() {
	return this->state;
}

void Player::hurt(float damage) {
	this->life -= damage;

	if (this->life > PLAYER_LIFE) {
		this->life = PLAYER_LIFE;
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
		cocos2d::CCTexture2D* texture = SpriteUtil::createTexture("citizenplayershotgun.png");
		SpriteUtil::setTexture(this->sprite, texture);
		break;
	}
	case SMG_: {
		this->weapon = new SMG(this->model);
		cocos2d::CCTexture2D* texture = SpriteUtil::createTexture("citizenplayer_uzi.png");
		SpriteUtil::setTexture(this->sprite, texture);
		break;
	}
	default:{
		this->weapon = new Weapon(this->model);
		cocos2d::CCTexture2D* texture = SpriteUtil::createTexture("citizenplayer_handgun.png");
		SpriteUtil::setTexture(this->sprite, texture);
	}
	}
}

} /* namespace dxco */
