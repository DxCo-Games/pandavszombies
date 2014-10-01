#include "GameTypeSelectionLayer.h"

#include "../../dxco/SpriteUtil.h"

namespace dxco {

GameTypeSelectionLayer::GameTypeSelectionLayer() {

}

cocos2d::CCScene* GameTypeSelectionLayer::scene() {

	cocos2d::CCScene *scene = cocos2d::CCScene::create();
	GameTypeSelectionLayer* layer = new GameTypeSelectionLayer();

	layer->init();
	scene->addChild(layer);

	return scene;
}

bool GameTypeSelectionLayer::init() {
	if (!cocos2d::CCLayer::init()) {
		return false;
	}

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	cocos2d::CCSprite* spriteBackground = SpriteUtil::create("fondo_ciudad.jpg", 0, 0, visibleSize.width, visibleSize.height);
	this->addChild(spriteBackground);

	cocos2d::CCSprite* survivalButtonSprite = SpriteUtil::create("buttons/survival_button.png", visibleSize.width * 0.2, visibleSize.height * 0.5,
																  visibleSize.width * 0.3, visibleSize.height * 0.15);

	this->addChild(survivalButtonSprite);
	this->survivalButton = new SurvivalButton(survivalButtonSprite);

	cocos2d::CCSprite* storyButtonSprite = SpriteUtil::create("buttons/story_button.png", visibleSize.width * 0.5, visibleSize.height * 0.5,
																  visibleSize.width * 0.3, visibleSize.height * 0.15);

	this->addChild(storyButtonSprite);
	this->storyButton = new StoryButton(storyButtonSprite);

	this->setTouchEnabled(true);

	return true;
}

void GameTypeSelectionLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {

	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
	cocos2d::CCPoint location = touch->getLocationInView();
	location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

	this->survivalButton->touch(location);
	this->storyButton->touch(location);
}


} /* namespace dxco */
