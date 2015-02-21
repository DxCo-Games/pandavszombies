#include "Bosszilla.h"

namespace dxco {

Bosszilla::Bosszilla(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int level, std::string type):
		Boss(model, sprite, animations, level, type),
		Item(sprite, animations){
	//fix superboss parameters
	this->life *= 100;
	this->strength *= 20;
	this->mass *= 2.5;
	this->speed *= 0.5;

	//make it always chase the player
	this->wander_range *= 3;
}

float Bosszilla::getColitionRatio() {
	return 0.1 * this->getWidth();
}

} /* namespace dxco */
