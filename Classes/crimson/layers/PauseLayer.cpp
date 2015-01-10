#include "PauseLayer.h"

#include "../../dxco/SpriteUtil.h"

namespace dxco {

PauseLayer::PauseLayer(GameModel* model, float x, float y, float width, float height) : Container(x, y, width, height) {

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	cocos2d::CCSprite* pauseTitle = SpriteUtil::create("pause_title.png", visibleSize.width * 0.3, visibleSize.height * 0.5, visibleSize.width * 0.4, visibleSize.height * 0.15);

	this->addChild(pauseTitle);

	float posicionY = visibleSize.height * 0.38;

	cocos2d::CCSprite* tryAgainButtonSprite = SpriteUtil::create("buttons/try_again_button.png", visibleSize.width * 0.32, posicionY, pauseTitle);
	cocos2d::CCSprite* menuButtonSprite = SpriteUtil::create("buttons/menu_icon_button.png", visibleSize.width * 0.45, posicionY, pauseTitle);
	cocos2d::CCSprite* resumeButtonSprite = SpriteUtil::create("buttons/play_icon_button.png", visibleSize.width * 0.58, posicionY, pauseTitle);

	this->addChild(tryAgainButtonSprite);
	this->addChild(menuButtonSprite);
	this->addChild(resumeButtonSprite);

	this->hide();

	this->tryAgainButton = new RestartSurvivalButton(model, tryAgainButtonSprite);

	this->menuButton = new GameTypeSelectionButton(menuButtonSprite);

	this->resumeButton = new ResumeButton(model, resumeButtonSprite);
}

void PauseLayer::show() {
	this->setVisible(true);
	this->setTouchEnabled(true);
}

void PauseLayer::hide() {
	this->setTouchEnabled(false);
	this->setVisible(false);
}

void PauseLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {

	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
	cocos2d::CCPoint location = touch->getLocationInView();
	location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

	this->menuButton->touch(location);
	this->tryAgainButton->touch(location);
	this->resumeButton->touch(location);
}

} /* namespace dxco */
