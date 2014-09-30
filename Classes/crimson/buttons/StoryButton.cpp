#include "StoryButton.h"

#include "../../HelloWorldScene.h"

namespace dxco {

StoryButton::StoryButton(cocos2d::CCSprite* sprite) : ButtonDxCo(sprite) {
	this->on();
}

void StoryButton::execute() {
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->runWithScene(HelloWorld::scene(false));
}

} /* namespace dxco */
