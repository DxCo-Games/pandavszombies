#include "SurvivalLevelFinishedLayer.h"

#include "../../dxco/SpriteUtil.h"

namespace dxco {

SurvivalLevelFinishedLayer::SurvivalLevelFinishedLayer() {
	this->menuButton = NULL;
	this->tryAgainButton = NULL;
}

bool SurvivalLevelFinishedLayer::init() {
	if (!cocos2d::CCLayer::init()) {
		return false;
	}

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	cocos2d::CCSprite* spriteBackground = SpriteUtil::create("fondo_ciudad.jpg", 0, 0, visibleSize.width, visibleSize.height);
	this->addChild(spriteBackground);

	cocos2d::CCSprite* menuButtonSprite = SpriteUtil::create("buttons/menu_button.png", visibleSize.width * 0.5, visibleSize.height * 0.5,
															  visibleSize.width * 0.3, visibleSize.height * 0.15);

	this->addChild(menuButtonSprite);
	this->menuButton = new GameTypeSelectionButton(menuButtonSprite);

	cocos2d::CCSprite* tryAgainButtonSprite = SpriteUtil::create("buttons/try_again_button.png", visibleSize.width * 0.5, visibleSize.height * 0.5,
															  visibleSize.width * 0.3, visibleSize.height * 0.15);

	this->addChild(tryAgainButtonSprite);
	this->tryAgainButton = new SurvivalButton(tryAgainButtonSprite);

	this->setTouchEnabled(true);

	return true;
}

cocos2d::CCScene* SurvivalLevelFinishedLayer::scene() {

	cocos2d::CCScene *scene = cocos2d::CCScene::create();
	SurvivalLevelFinishedLayer* layer = new SurvivalLevelFinishedLayer();

	layer->init();
	scene->addChild(layer);

	return scene;
}

void SurvivalLevelFinishedLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {

	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
	cocos2d::CCPoint location = touch->getLocationInView();
	location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

	this->menuButton->touch(location);
}

} /* namespace dxco */