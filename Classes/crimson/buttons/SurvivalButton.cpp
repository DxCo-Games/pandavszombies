#include "SurvivalButton.h"

#include "../../HelloWorldScene.h"

namespace dxco {

SurvivalButton::SurvivalButton(cocos2d::CCSprite* sprite) : ButtonDxCo(sprite) {
	this->on();
}

void SurvivalButton::execute() {
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->runWithScene(HelloWorld::scene(true));
}

} /* namespace dxco */
