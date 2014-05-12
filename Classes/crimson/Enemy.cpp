#include "Enemy.h"
#include "GameModel.h"

namespace dxco {

Enemy::Enemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : Item(sprite, animations) {
	this->model = model;
}

void Enemy::update(float dt);

} /* namespace dxco */
