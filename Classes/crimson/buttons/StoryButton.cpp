#include "StoryButton.h"

#include "../layers/LevelSelectionLayer.h"

namespace dxco {

StoryButton::StoryButton(cocos2d::CCSprite* sprite, int currentPage) : ButtonDxCo(sprite) {
	this->currentPage = currentPage;
	this->on();
}

void StoryButton::execute() {
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->pushScene(LevelSelectionLayer::scene(currentPage));
}

} /* namespace dxco */
