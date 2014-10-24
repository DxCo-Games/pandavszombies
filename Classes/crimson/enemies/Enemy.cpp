#include "Enemy.h"
#include "../GameModel.h"
#include "../ChainedKillsManager.h"
#include "../../dxco/SpriteUtil.h"
#include "../../dxco/MathUtil.h"
#include "cocos2d.h"
#include "../Player.h"
#include "../FireWeapon.h"
#include <algorithm>

namespace dxco {

//initialize the default level. can't do it in Enemy.h gotta love cpp
int Enemy::ENEMY_LEVEL = 1;

float Enemy::getSpeed() {
	return 20 + 5* Enemy::ENEMY_LEVEL;
}

Enemy::Enemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int level) :
		TopDownItem(ENEMY_ANGLE_POSITIONS), SteeringBehaviorItem(Enemy::getSpeed(), 0.25 * ENEMY_DEFAULT_SPEED / Enemy::getSpeed()),
		Item(sprite, animations){
	this->model = model;
	this->life = 10 * (level + 1);
	this->score = 10 * (level + 1);
	this->strength = 5 * (level + 1);
	this->burning = false;
	this->state = ENEMY_STANDING;
	this->action = NULL;
	this->dead = false;
}

void Enemy::setNewWanderTarget() {
	this->wanderTarget = cocos2d::CCPoint(rand() % (int)this->model->mapa->getWidth(),
			rand() % (int)this->model->mapa->getHeight());
}

void Enemy::freeze() {
	cocos2d::CCAction* freezeAction = cocos2d::CCSequence::create(cocos2d::CCTintTo::create(0.05f, 98, 253, 253), NULL);
	this->getSprite()->runAction(freezeAction);
}

void Enemy::unfreeze() {
	cocos2d::CCAction* unfreezeAction = cocos2d::CCSequence::create(cocos2d::CCTintTo::create(0.05f, 255, 255, 255), NULL);
	this->getSprite()->runAction(unfreezeAction);
}

void Enemy::update(float dt) {

	if (!this->model->freezeBonusActivated || !this->isActive()) {
		Item::update(dt);
	}

	if (this->isActive()) {

		cocos2d::CCPoint playerLocation = this->model->player->getLocation();
		float dist = MathUtil::distance(this->getLocation(), playerLocation);
		float angle = MathUtil::angle(cocos2d::CCPointZero, this->currentVelocity) * -57.2957795;

		if (!this->model->freezeBonusActivated) {
			this->state = ENEMY_WALKING;

			//Enable behaviors according to distance from target
			int behaviors;
			if (dist > ENEMY_WANDER_RANGE) {
				behaviors = USE_WANDER;
			} else if (dist > ENEMY_SEEK_RANGE) {
				behaviors = USE_SEEK;
			} else if (dist > ENEMY_ARRIVE_RANGE) {
				behaviors = USE_ARRIVE;
			} else {
				behaviors = USE_STAND;
			}
			behaviors = behaviors | USE_SEPARATION;
			this->updateBehaviors(dt, behaviors, playerLocation, dist,
					this->model->items, ENEMY_SEEK_RANGE - ENEMY_ARRIVE_RANGE, ENEMY_ARRIVE_RANGE);

			//look at destiny
			this->setRotation(angle);
		}

		this->burn(dt, playerLocation, dist, angle);
		//after updating, if it's alive fix position
		this->fixZOrder(playerLocation.y);
	} else {
		this->bloodDt += dt;

		Animation *animation = this->animations.find(this->getState())->second;
		if (animation->finished && this->bloodDt > ENEMY_BLOOD_DURATION) {
			if (!this->action) {
				this->getSprite()->stopAllActions(); // Stop fadeIn action
				this->action = SpriteUtil::fadeOut(this->getSprite(), 0.75);
			}

			if (this->bloodDt > ENEMY_BLOOD_DURATION + 1) {
				// FadeOut is over. IsDone doesn't work because action is already released
				this->sprite->removeFromParent();

				//this removes the enemies. cpp, don't ask.
				this->model->enemies.erase(std::remove(this->model->enemies.begin(), this->model->enemies.end(), this),
				this->model->enemies.end());
				this->model->items.erase(std::remove(this->model->items.begin(), this->model->items.end(), this),
				this->model->items.end());
			}
		}
	}
}

void Enemy::stand(float dt, cocos2d::CCPoint target) {
	//close to the enemy -> attack
	this->state = ENEMY_STANDING;
	this->beat(this->model->player, dt);
	SteeringBehaviorItem::stand(dt, target);
}

void Enemy::kill() {
	if (this->model->freezeBonusActivated) {
		this->unfreeze();
	}
	//fix zorder of blood splat to be on the floor
	this->sprite->setZOrder(-1);
	this->state = ENEMY_DEAD;
	this->bloodDt = 0;
	this->model->enemyKilled(this);
}

void Enemy::fixZOrder(float playerY) {
	//update z order for isometric ordering of characters. if floor put at the bottom
	if(this->isActive()){
		float enemyBottom = this->getBottomPosition();
		int zorder = 1000 - enemyBottom * 1000 / this->model->mapa->getHeight();
		this->model->mapa->reorderChild(this->sprite, zorder);
	}
}

void Enemy::beat(Player* player, float dt) {
	//make damage
	player->hurt(this->strength * dt);

	if (!player->shieldActivated) {
		cocos2d::CCAction* hurtAction = cocos2d::CCSequence::create(cocos2d::CCTintTo::create(0.01f, 255, 0, 0), cocos2d::CCTintTo::create(0.01f, 255, 255, 255), NULL);
		player->getSprite()->runAction(hurtAction);
	}
}

bool Enemy::shoot(Bullet* bullet) {
	bool result = false;

	if (bullet && !bullet->used && this->isActive()) {

		float distance = MathUtil::distance(this->getLocation(),
				bullet->getLocation());

		if (distance < this->getWidth() / 3) {
			bullet->use();
			result = true;

			this->hurt(bullet->getDamage());
		}
	}

	return result;
}

void Enemy::hurt(float value) {
	this->life -= value;
	if (!this->isActive()) {
		this->kill();
	} else if (!this->model->freezeBonusActivated) {
		cocos2d::CCAction* hurtAction = cocos2d::CCSequence::create(cocos2d::CCTintTo::create(0.05f, 255, 0, 0), cocos2d::CCTintTo::create(0.05f, 255, 255, 255), NULL);
		this->getSprite()->runAction(hurtAction);
	}
}

void Enemy::burn(float dt, cocos2d::CCPoint playerLocation, float distance, float angle) {
	float wasBurning = this->burning;
	/*If has fire weapon and close to the player and in front of the player */
	this->burning =(this->model->player->weaponType == Player::FIRE &&
			distance < this->model->player->getWidth() * 1.5 &&
			abs(abs(this->model->player->getRotation() - angle) - 180) < 60);

	if (this->burning && wasBurning){
		this->hurt(FIRE_DAMAGE * dt);
	}
}

float Enemy::getColitionRatio() {
	return 0.1 * this->getWidth();
}

bool Enemy::isActive() {
	return this->life > 0;
}

} /* namespace dxco */