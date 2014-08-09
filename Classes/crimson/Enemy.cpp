#include "Enemy.h"
#include "GameModel.h"
#include "../dxco/SpriteUtil.h"
#include "../dxco/MathUtil.h"
#include "cocos2d.h"
#include "Player.h"
#include "FireWeapon.h"
#include <algorithm>

namespace dxco {

//initialize the default speed. can't do it in Enemy.h gotta love cpp
int Enemy::ENEMY_SPEED = 15;

Enemy::Enemy(GameModel* model, cocos2d::CCSprite* sprite,
		std::map<int, Animation*>& animations) :
		TopDownItem(sprite, animations, ENEMY_ANGLE_POSITIONS) {
	this->model = model;
	this->life = 20;
	this->score = 10;
	this->strength = 10;
	this->burning = false;
	this->state = ENEMY_STANDING;
	this->action = NULL;
	this->dead = false;
	this->up = true;
	this->upTime = 0;

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
		float radian_angle = MathUtil::angle(this->getLocation(), destiny);
		float angle = radian_angle * -57.2957795;
		this->setRotation(angle);

		this->burn(dt, playerLocation, distance, angle);

		if (distance < this->getWidth() / 4 + this->model->player->getWidth() / 4) {
			//if close to the player, attacl
			this->state = ENEMY_STANDING;
			this->beat(this->model->player, dt);

			/* cuando estoy al lado del panda, hago que los zombies peguen
			saltitos */
			this->upTime += dt;

			if (this->up) {

				if (this->upTime > 0.15) {
					this->up = false;
					this->upTime = 0;
				}
				SpriteUtil::move(this->getSprite(), 75 * cos (radian_angle) * dt, 75 * sin(radian_angle) * dt);
			} else {
				if (this->upTime > 0.15) {
					this->up = true;
					this->upTime = 0;
				}

				SpriteUtil::move(this->getSprite(), -75 * cos (radian_angle) * dt, -75 * sin(radian_angle) * dt);
			}

		} else {

			if (this->canAdvance(destiny, ENEMY_SPEED * dt, this->model->getItems())) {
				//walk to destiny
				cocos2d::CCPoint oldPosition = this->getLocation();
				this->goTo(destiny, ENEMY_SPEED * dt);

				//before putting it to walk, make sure it will be able to keep moving
				if (this->canAdvance(destiny, ENEMY_SPEED * dt, this->model->getItems())) {
					this->state = ENEMY_WALKING;
					//update z order for isometric ordering of characters
					int zorder = 100 - this->getLocation().y * 100 / this->model->mapa->getHeight();
					this->model->mapa->reorderChild(this->sprite, zorder);
				} else {
					//if it can't move further, undo this movement.
					this->goTo(destiny, - ENEMY_SPEED * dt);
				}

			} else {
				this->state = ENEMY_STANDING;
				if (this->dumb) {
					//if it's dumb and got blocked, try a new direction
					this->setDumbDestiny();
					if (!this->canAdvance(*this->destiny, ENEMY_SPEED * dt, this->model->getItems())) {
						//if still blocked just follow the player
						this->dumb = false;
					}
				}
			}
		}
	} else {
		if (!dead) { // First time only
			dead = true;
			this->getSprite()->stopAllActions(); // Stop fadeIn action
			this->action = SpriteUtil::fadeOut(this->getSprite(), 0.25);
			this->model->bonusFactory->createBonus(this->model, this->getLocation());
		}

		if (this->action == NULL) { // FadeOut is over. IsDone doesn't work because action is already released
			this->model->mapa->removeChild(this->getSprite());

			//this removes the enemies. cpp, don't ask.
			this->model->enemies.erase(std::remove(this->model->enemies.begin(), this->model->enemies.end(), this),
			this->model->enemies.end());
			this->model->items.erase(std::remove(this->model->items.begin(), this->model->items.end(), this),
			this->model->items.end());
		}
	}
}

void Enemy::beat(Player* player, float dt) {
	//make damage
	player->hurt(this->strength * dt);
}

bool Enemy::shoot(Bullet* bullet) {
	bool result = false;

	if (bullet && !bullet->used && this->isActive()) {

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
			distance < this->model->player->getWidth() &&
			abs(abs(this->model->player->getRotation() - angle) - 180) < 60);

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
