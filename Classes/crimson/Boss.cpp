#include "Boss.h"

namespace dxco {

Boss::Boss(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) :
	Enemy(model, sprite, animations){
	this->life = 120;
	this->score = 50;
	this->strength = 50;
	this->dumb = false;
}


} /* namespace dxco */
