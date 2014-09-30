#include "Boss.h"

namespace dxco {

Boss::Boss(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, float speed) :
	Enemy(model, sprite, animations, speed),
	Item(sprite, animations) {
	this->life = 120;
	this->score = 50;
	this->strength = 50;
	this->mass = 1.5;
}

float Boss::getColitionRatio() {
	return 0.2 * this->getWidth();
}


} /* namespace dxco */
