#include "GameTypeSelectionLayer.h"
#include "../GameProperties.h"
#include "../../dxco/SpriteUtil.h"

namespace dxco {

GameTypeSelectionLayer::GameTypeSelectionLayer() {
	this->storyButton = NULL;
	this->survivalButton = NULL;
	this->equipPandaButton = NULL;
	this->frenzyButton = NULL;
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

	int frenzy = GameProperties::get("frenzy.unlocked");

	cocos2d::CCSprite* storyButtonSprite = this->getSprite("buttons/story_button.png", 2 + frenzy);
	this->addChild(storyButtonSprite);
	this->storyButton = new StoryButton(storyButtonSprite);

	cocos2d::CCSprite* survivalButtonSprite = this->getSprite("buttons/survival_button.png", 1 + frenzy);
	SpriteUtil::leftAlign(storyButtonSprite, survivalButtonSprite);
	this->addChild(survivalButtonSprite);
	this->survivalButton = new SurvivalButton(survivalButtonSprite);

	if (frenzy) {
		cocos2d::CCSprite* frenzyButtonSprite = this->getSprite("buttons/frenzy_button.png", 1);
		SpriteUtil::leftAlign(storyButtonSprite, frenzyButtonSprite);
		this->addChild(frenzyButtonSprite);
		this->frenzyButton = new SurvivalButton(frenzyButtonSprite, true);
	}

	cocos2d::CCSprite* equipButtonSprite = this->getSprite("buttons/equip_panda_button_text.png", 0);
	SpriteUtil::leftAlign(storyButtonSprite, equipButtonSprite);
	this->addChild(equipButtonSprite);
	this->equipPandaButton = new EquipPandaButton(equipButtonSprite);

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	return true;
}

cocos2d::CCSprite* GameTypeSelectionLayer::getSprite(std::string texture, int index) {
	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	float buttonWidth = visibleSize.width * 0.25;
	float buttonHeight = buttonWidth * 0.32;
	float ypadding = buttonHeight * 0.18;

	int total = 3;
	if (GameProperties::get("frenzy.unlocked")) {
		total = 4;
	}

	float ymargin = (visibleSize.height - (total -1)*ypadding - total*buttonHeight) / 2;
	float xmargin = (visibleSize.width - buttonWidth) / 2;

	return SpriteUtil::create(texture, xmargin, ymargin + index*buttonHeight + index*ypadding,
				buttonWidth, buttonHeight);
}

void GameTypeSelectionLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {

	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
	cocos2d::CCPoint location = touch->getLocationInView();
	location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

	this->survivalButton->touch(location);
	this->storyButton->touch(location);
	this->equipPandaButton->touch(location);

	if (this->frenzyButton != NULL) {
		this->frenzyButton->touch(location);
	}
}


} /* namespace dxco */
