#include "NextLevelButton.h"

#include "../../HelloWorldScene.h"

#include "SimpleAudioEngine.h"

namespace dxco {

NextLevelButton::NextLevelButton(cocos2d::CCSprite* sprite, int levelNumber) : ButtonDxCo(sprite) {
	this->on();
	this->levelNumber = levelNumber;
}

void NextLevelButton::execute() {
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->replaceScene(HelloWorld::scene(false, false, this->levelNumber));

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

} /* namespace dxco */
