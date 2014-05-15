#include "Enemy.h"
#include "GameModel.h"
#include "../dxco/SpriteUtil.h"
#include "../dxco/MathUtil.h"
#include "cocos2d.h"
#include "Player.h"

namespace dxco {

Enemy::Enemy(GameModel* model, cocos2d::CCSprite* sprite,
		std::map<int, Animation*>& animations) :
		Item(sprite, animations) {
	this->model = model;
	this->life = 20;
	this->deadTime = 0;
	this->strength = 10;
}

void Enemy::update(float dt) {

	Item::update(dt);
	if (this->isActive()) {
		float distance = MathUtil::distance(this->getLocation(),
				this->model->player->getLocation());

		if (distance < this->getWidth() + this->model->player->getWidth() / 4) {
			this->beat(this->model->player, dt);
		} else {
			this->state = ENEMY_WALKING;
			//look at player
			float angle = MathUtil::angle(this->getLocation(),
					this->model->player->getLocation()) * -57.2957795;
			SpriteUtil::setAngle(this->sprite, angle);

			if (this->canAdvance(this->model->player->getLocation(),
							ENEMY_SPEED * dt, this->model->getItems())) {
				//walk to player
				this->goTo(this->model->player->getLocation(), ENEMY_SPEED * dt);
			}
		}
	} else {
		this->state = ENEMY_DEAD;
		this->sprite->setZOrder(-1);
		this->deadTime += dt;

		if (this->deadTime > ENEMY_DEAD_TIME) {
			this->getSprite()->setVisible(false);
		}
	}
}

void Enemy::beat(Player* player, float dt) {
	if (this->state != ENEMY_BEATING) {
		//start to attack
		this->state = ENEMY_BEATING;
	} else {
		//already atacking -> make damage
		player->hurt(this->strength * dt);
	}
}

bool Enemy::shoot(Bullet* bullet) {
	bool result = false;

	if (bullet && !bullet->used) {

		float distance = MathUtil::distance(this->getLocation(),
				bullet->getLocation());

		if (distance < this->getWidth() / 2) {
			bullet->use();
			result = true;

			this->life -= bullet->getDamage();
		}
	}

	return result;
}

void Enemy::hurt(float value) {
	this->life -= value;
}

float Enemy::getWidth() {
	return Item::getWidth() / 2;
}
bool Enemy::isActive() {
	return this->life > 0;
}

} /* namespace dxco */
