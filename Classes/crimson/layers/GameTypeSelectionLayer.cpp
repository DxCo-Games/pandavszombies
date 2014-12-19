#include "GameTypeSelectionLayer.h"
#include "../../dxco/SpriteUtil.h"

namespace dxco {

GameTypeSelectionLayer::GameTypeSelectionLayer() {
	this->storyButton = NULL;
	this->survivalButton = NULL;
	this->equipPandaButton = NULL;
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

	float buttonWidth = visibleSize.width * 0.25;
	float buttonHeight = buttonWidth * 0.32;
	float ypadding = buttonHeight * 0.18;
	float ymargin = (visibleSize.height - 3*ypadding - 4*buttonHeight) / 2;
	float xmargin = (visibleSize.width - buttonWidth) / 2;

	cocos2d::CCSprite* storyButtonSprite = SpriteUtil::create("buttons/story_button.png", xmargin, ymargin + 3*buttonHeight + 3*ypadding,
			buttonWidth, buttonHeight);
	this->addChild(storyButtonSprite);
	this->storyButton = new StoryButton(storyButtonSprite);

	cocos2d::CCSprite* survivalButtonSprite = SpriteUtil::create("buttons/survival_button.png", xmargin, ymargin + 2*buttonHeight + 2*ypadding,
			storyButtonSprite);
	SpriteUtil::leftAlign(storyButtonSprite, survivalButtonSprite);
	this->addChild(survivalButtonSprite);
	this->survivalButton = new SurvivalButton(survivalButtonSprite);

	cocos2d::CCSprite* challengeButtonSprite = SpriteUtil::create("buttons/challenge_button.png", xmargin, ymargin + buttonHeight + ypadding,
			storyButtonSprite);
	SpriteUtil::leftAlign(storyButtonSprite, challengeButtonSprite);
	this->addChild(challengeButtonSprite);

	cocos2d::CCSprite* equipButtonSprite = SpriteUtil::create("buttons/equip_panda_button_text.png", xmargin, ymargin,
			storyButtonSprite);
	SpriteUtil::leftAlign(storyButtonSprite, equipButtonSprite);
	this->addChild(equipButtonSprite);
	this->equipPandaButton = new EquipPandaButton(equipButtonSprite);

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	return true;
}

void GameTypeSelectionLayer::keyBackClicked() {
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->end();
}

void GameTypeSelectionLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {

	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
	cocos2d::CCPoint location = touch->getLocationInView();
	location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

	this->survivalButton->touch(location);
	this->storyButton->touch(location);
	this->equipPandaButton->touch(location);
}


} /* namespace dxco */
