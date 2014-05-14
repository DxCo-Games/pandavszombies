#include "Player.h"
#include "Bullet.h"
#include "GameModel.h"
#include "../dxco/SpriteUtil.h"



namespace dxco {

Player::Player(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : Item(sprite, animations) {
	this->state = QUIETO;
}

void Player::disparar() {
	cocos2d::CCPoint location = this->getLocation();

	cocos2d::CCSprite* spriteBullet = SpriteUtil::create("bullet.png", location.x, location.y, 5, 5);
	/** degrees to radians */
	float rotation = this->getSprite()->getRotation();
	float angle = -rotation / 57.2957795;

	spriteBullet->setRotation(rotation);

	//fix position of the bullet to actually come out the weapon. the last number fixes sprites nonesense
	float R = 18;
	SpriteUtil::moveTo(spriteBullet, location.x + R * cos(angle), location.y + R * sin(angle) - 16);

	std::map<int, Animation*> animations;
	Bullet* bullet = new Bullet(spriteBullet, angle, animations);
	this->model->addBullet(bullet);
}

int Player::getState() {
	return this->state;
}

} /* namespace dxco */
