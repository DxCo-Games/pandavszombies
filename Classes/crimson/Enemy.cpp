#include "Enemy.h"
#include "GameModel.h"
#include "../dxco/SpriteUtil.h"
#include "../dxco/MathUtil.h"

namespace dxco {

Enemy::Enemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : Item(sprite, animations) {
	this->model = model;
	this->muerto = false;
}

void Enemy::update(float dt) {
	//look at player
	float angle = MathUtil::angle(this->getLocation(), this->model->player->getLocation()) * - 57.2957795;
	SpriteUtil::setAngle(this->sprite, angle);
	//walk to player
	this->goTo(this->model->player->getLocation(), ENEMY_SPEED * dt);
}

bool Enemy::shoot(Bullet* bullet) {
	bool result = false;

	if (bullet) {
		float distance = MathUtil::distance(this->getLocation(), bullet->getLocation());

		if (distance < this->getWidth() / 2) {
			result = true;
			this->muerto = true;
		}
	}

	return result;
}

} /* namespace dxco */
