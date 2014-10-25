#include "LevelSelectionLayer.h"
#include "../../dxco/SpriteUtil.h"
#include "../buttons/LevelButton.h"

namespace dxco {

LevelSelectionLayer::LevelSelectionLayer() {
	// TODO Auto-generated constructor stub

}

cocos2d::CCScene* LevelSelectionLayer::scene() {

	cocos2d::CCScene *scene = cocos2d::CCScene::create();
	LevelSelectionLayer* layer = new LevelSelectionLayer();

	layer->init();
	scene->addChild(layer);

	return scene;
}

bool LevelSelectionLayer::init() {
	if (!cocos2d::CCLayer::init()) {
		return false;
	}

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	cocos2d::CCSprite* spriteBackground = SpriteUtil::create("fondo_ciudad.jpg", 0, 0, visibleSize.width, visibleSize.height);
	this->addChild(spriteBackground);

	//just to get dimensions :P
	LevelButton button = LevelButton(1, 0, 0);
	float buttonWidth = SpriteUtil::getWidth((cocos2d::CCSprite*)button.sprite);
	float xpadding = buttonWidth * 0.05;
	float xmargin = (visibleSize.width - 10*buttonWidth - 9*xpadding) / 2;

	float buttonHeight = SpriteUtil::getHeight((cocos2d::CCSprite*)button.sprite);
	float ypadding = buttonHeight* 0.01;
	float ymargin = (visibleSize.height - buttonHeight*2 - ypadding) / 2;

	float y = ymargin + buttonHeight + ypadding;
	for (int i=0; i < 10 ;i++) {
		float x = xmargin + i * buttonWidth;
		LevelButton *button = new LevelButton(i+1, x, y);
		this->buttons.push_back(button);
		this->addChild(button->sprite);
	}

	y = ymargin;
	for (int i=0; i < 10 ;i++) {
		float x = xmargin + i * buttonWidth;
		LevelButton *button = new LevelButton(i+11, x, y);
		this->buttons.push_back(button);
		this->addChild(button->sprite);
	}

	this->setTouchEnabled(true);


	return true;
}

void LevelSelectionLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {

	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
	cocos2d::CCPoint location = touch->getLocationInView();
	location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

//	this->survivalButton->touch(location);
//	this->storyButton->touch(location);
}

} /* namespace dxco */
