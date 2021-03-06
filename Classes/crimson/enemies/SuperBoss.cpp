#include "SuperBoss.h"

namespace dxco {

SuperBoss::SuperBoss(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int level, std::string type):
		Boss(model, sprite, animations, level, type),
		Item(sprite, animations){
	//fix superboss parameters
	this->life *= 30;
	this->strength *= 5;
	this->mass *= 1.8;
	this->speed *= 0.65;

	//make it always chase the player
	this->wander_range *= 3;
}

float SuperBoss::getColitionRatio() {
	return 0.15 * this->getWidth();
}

} /* namespace dxco */
