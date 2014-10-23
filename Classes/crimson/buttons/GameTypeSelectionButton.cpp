#include "GameTypeSelectionButton.h"

#include "SimpleAudioEngine.h"

#include "../layers/GameTypeSelectionLayer.h"

namespace dxco {

GameTypeSelectionButton::GameTypeSelectionButton(cocos2d::CCSprite* sprite) : ButtonDxCo(sprite) {
	this->on();
}

void GameTypeSelectionButton::execute() {
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->runWithScene(GameTypeSelectionLayer::scene());

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

} /* namespace dxco */
