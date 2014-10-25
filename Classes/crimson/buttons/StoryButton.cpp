#include "StoryButton.h"

#include "../layers/LevelSelectionLayer.h"

namespace dxco {

StoryButton::StoryButton(cocos2d::CCSprite* sprite) : ButtonDxCo(sprite) {
	this->on();
}

void StoryButton::execute() {
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->runWithScene(LevelSelectionLayer::scene());
}

} /* namespace dxco */
