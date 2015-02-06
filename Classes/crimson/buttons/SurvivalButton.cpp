#include "SurvivalButton.h"

#include "../../HelloWorldScene.h"

namespace dxco {

SurvivalButton::SurvivalButton(cocos2d::CCSprite* sprite, bool frenzy) : ButtonDxCo(sprite) {
	this->on();
	this->frenzy = frenzy;
}

void SurvivalButton::execute() {
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	if (this->frenzy) {
		pDirector->replaceScene(HelloWorld::scene(false, true));
	} else {
		pDirector->replaceScene(HelloWorld::scene(true, false));
	}
}

} /* namespace dxco */
