#include "Enemy.h"
#include "GameModel.h"

namespace dxco {

Enemy::Enemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : Item(sprite, animations) {
	this->model = model;
}

void Enemy::update(float dt) {
	this->goTo(this->model->player->getLocation(), ENEMY_SPEED * dt);
}

} /* namespace dxco */
