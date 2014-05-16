#include "Player.h"
#include "Bullet.h"
#include "GameModel.h"
#include "Weapon.h"
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
	switch(type) {
	case SHOTGUN:;
	case SMG:;
	default:
		this->weapon = new Weapon(this->model);
	}
}

} /* namespace dxco */
