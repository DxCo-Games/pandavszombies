#include "LevelScreenButton.h"
#include "../layers/LevelSelectionLayer.h"

namespace dxco {

LevelScreenButton::LevelScreenButton(cocos2d::CCSprite* sprite, int page) : ButtonDxCo(sprite) {
	this->page = page;
	this->on();
}

void LevelScreenButton::execute() {
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->replaceScene(LevelSelectionLayer::scene(this->page));
}

} /* namespace dxco */
