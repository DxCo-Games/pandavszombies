#include "Player.h"
#include "Bullet.h"
#include "GameModel.h"
#include "../dxco/SpriteUtil.h"

namespace dxco {

Player::Player(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : Item(sprite, animations) {

}

void Player::disparar() {
	cocos2d::CCPoint location = this->getLocation();
	cocos2d::CCSprite* spriteBullet = SpriteUtil::create("bullet.jpg", location.x - 5 -15, location.y - 1.5 - 15, 10, 3);

	/** transformo el angulo a radianes */
	float rotation = this->getSprite()->getRotation();
	float angle = -rotation / 57.2957795;

	spriteBullet->setRotation(rotation);

	std::map<int, Animation*> animations;
	Bullet* bullet = new Bullet(spriteBullet, angle, animations);
	this->model->addBullet(bullet);
}

} /* namespace dxco */
