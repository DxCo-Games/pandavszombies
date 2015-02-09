#include "PauseLayer.h"

#include "../../dxco/SpriteUtil.h"

namespace dxco {

PauseLayer::PauseLayer(GameModel* model, float x, float y, float width, float height, cocos2d::CCSprite* scaleMaster) : Container(x, y, width, height) {

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	cocos2d::CCSprite* pauseTitle = SpriteUtil::create("pause_title.png", visibleSize.width * 0.38, visibleSize.height * 0.58, scaleMaster);
	this->addChild(pauseTitle);

	pauseTitle->setScaleX(pauseTitle->getScaleX()* 1.1);
	pauseTitle->setScaleY(pauseTitle->getScaleY()* 1.1);

	float posicionY = visibleSize.height * 0.46;

	cocos2d::CCSprite* tryAgainButtonSprite = SpriteUtil::create("buttons/try_again_button.png", 0, posicionY, pauseTitle);
	SpriteUtil::leftAlign(pauseTitle, tryAgainButtonSprite);
	cocos2d::CCSprite* resumeButtonSprite = SpriteUtil::create("buttons/play_icon_button.png", 0, posicionY, pauseTitle);
	SpriteUtil::rightAlign(pauseTitle, resumeButtonSprite);
	cocos2d::CCSprite* menuButtonSprite = SpriteUtil::create("buttons/menu_icon_button.png", 0, posicionY, pauseTitle);
	menuButtonSprite->setPositionX((tryAgainButtonSprite->getPositionX() + resumeButtonSprite->getPositionX()) /2);

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
