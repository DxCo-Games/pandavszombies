#include "Enemy.h"
#include "GameModel.h"
#include "../dxco/SpriteUtil.h"
#include "../dxco/MathUtil.h"
#include "cocos2d.h"

namespace dxco {

Enemy::Enemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : Item(sprite, animations) {
	this->model = model;
	this->muerto = false;
	this->life = 20;
	this->deadTime = 0;
}

void Enemy::update(float dt) {

	if (!this->muerto) {

		if (this->canAdvance(this->model->player->getLocation(), ENEMY_SPEED * dt, this->model->getItems())) {
			//look at player
			float angle = MathUtil::angle(this->getLocation(), this->model->player->getLocation()) * - 57.2957795;
			SpriteUtil::setAngle(this->sprite, angle);
			//walk to player
			this->goTo(this->model->player->getLocation(), ENEMY_SPEED * dt);
		}
	} else {
		this->deadTime += dt;

		if (this->deadTime > ENEMY_DEAD_TIME) {
			this->getSprite()->setVisible(false);
		}
	}
}

bool Enemy::shoot(Bullet* bullet) {
	bool result = false;

	if (bullet && !bullet->used) {

		float distance = MathUtil::distance(this->getLocation(), bullet->getLocation());

		if (distance < this->getWidth() / 2) {
			bullet->use();
			result = true;

			this->life -= bullet->getDamage();

			if (this->life < 0) {
				this->muerto = true;
				cocos2d::CCPoint position = this->getLocation();
				SpriteUtil::setTexture(this->sprite, "tomb.png");
			}
		}
	}

	return result;
}

} /* namespace dxco */
