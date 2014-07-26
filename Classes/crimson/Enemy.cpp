#include "Enemy.h"
#include "GameModel.h"
#include "../dxco/SpriteUtil.h"
#include "../dxco/MathUtil.h"
#include "cocos2d.h"
#include "Player.h"
#include "FireWeapon.h"
#include <algorithm>

namespace dxco {

Enemy::Enemy(GameModel* model, cocos2d::CCSprite* sprite,
		std::map<int, Animation*>& animations) :
		TopDownItem(sprite, animations, ENEMY_ANGLE_POSITIONS) {
	this->model = model;
	this->life = 20;
	this->deadTime = 0;
	this->strength = 10;
	this->burning = false;
	this->state = ENEMY_WALKING;

	if (rand() % 2) {
		this->dumb = false;
	} else {
		this->dumb = true;
		this->setDumbDestiny();
	}
}

void Enemy::setDumbDestiny() {
	this->destiny = new cocos2d::CCPoint(rand() % (int)this->model->mapa->getWidth(),
					rand() % (int)this->model->mapa->getHeight());
}

void Enemy::update(float dt) {
	Item::update(dt);
	if (this->isActive()) {
		cocos2d::CCPoint playerLocation = this->model->player->getLocation();
		float distance = MathUtil::distance(this->getLocation(), playerLocation);

		if (distance < this->model->player->getWidth() * 2){
			//if close to player, start following him
			this->dumb = false;
		}

		cocos2d::CCPoint destiny;
		if (this->dumb) {
			float destinyDistance = MathUtil::distance(this->getLocation(), *this->destiny);
			if (destinyDistance < this->getWidth()) {
				//if close to destiny, renew it
				this->setDumbDestiny();
			}
			destiny = *this->destiny;
		} else {
			destiny = playerLocation;
		}

		//look at destiny
		float angle = MathUtil::angle(this->getLocation(), destiny) * -57.2957795;
//		SpriteUtil::setAngle(this->sprite, angle);
		this->setRotation(-360 - angle);

		this->burn(dt, playerLocation, distance, angle);

		if (distance < this->getWidth() / 4 + this->model->player->getWidth() / 4) {
			this->beat(this->model->player, dt);
		} else {
			this->state = ENEMY_WALKING;

			if (this->canAdvance(destiny, ENEMY_SPEED * dt, this->model->getItems())) {
				//walk to destiny
				this->goTo(destiny, ENEMY_SPEED * dt);
			} else if (this->dumb) {
				//if it's dumb and got blocked, try a new direction
				this->setDumbDestiny();
				if (!this->canAdvance(*this->destiny, ENEMY_SPEED * dt, this->model->getItems())) {
					//if still blocked just follow the player
					this->dumb = false;
				}
			}
		}
	} else {
		if (this->state != ENEMY_DEAD) {
			this->model->bonusFactory->createBonus(this->model, this->getLocation());
			this->state = ENEMY_DEAD;
			this->sprite->setZOrder(-1);
		}

		this->deadTime += dt;
		if (this->deadTime > ENEMY_DEAD_TIME) {
			this->getSprite()->setVisible(false);

			//this removes the enemies. cpp, don't ask.
			this->model->enemies.erase(std::remove(this->model->enemies.begin(), this->model->enemies.end(), this),
					this->model->enemies.end());
			this->model->items.erase(std::remove(this->model->items.begin(), this->model->items.end(), this),
								this->model->items.end());
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

	if (bullet && !bullet->used && this->state != ENEMY_DEAD) {

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

void Enemy::burn(float dt, cocos2d::CCPoint playerLocation, float distance, float angle) {
	float wasBurning = this->burning;
	/*If has fire weapon and close to the player and in front of the player */
	this->burning =(this->model->player->weaponType == Player::FIRE &&
			distance < this->model->player->getWidth() * 2 &&
			abs(abs(this->model->player->getRotation() - angle) - 180) < 60);

//	if (distance < this->model->player->getWidth() * 2) {
//		CCLOG("Rotation %f", this->model->player->getSprite()->getRotation());
//		CCLOG("Angulo %f", angle);
//	}
	if (this->burning && wasBurning){
		this->hurt(FIRE_DAMAGE * dt);
	}
}

float Enemy::getColitionRatio() {
	return this->getWidth() / 4;
}
bool Enemy::isActive() {
	return this->life > 0;
}

} /* namespace dxco */
