#include "LevelSelectionLayer.h"
#include "../../dxco/SpriteUtil.h"
#include "../buttons/LevelButton.h"
#include "../buttons/LevelScreenButton.h"
#include "../../dxco/StringUtil.h"
#include "../../dxco/DB.h"
#include "../../dxco/admob/AdmobHelper.h"

namespace dxco {

LevelSelectionLayer::LevelSelectionLayer() {
	this->page = 0;
	this->prev = NULL;
	this->next = NULL;
	this->touchId = 999;
}

cocos2d::CCScene* LevelSelectionLayer::scene(int page) {

	cocos2d::CCScene *scene = cocos2d::CCScene::create();
	LevelSelectionLayer* layer = new LevelSelectionLayer();

	layer->page = page;
	layer->init();
	scene->addChild(layer);

	return scene;
}

bool LevelSelectionLayer::init() {
	if (!cocos2d::CCLayer::init()) {
		return false;
	}

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	cocos2d::CCSprite* spriteBackground;

	if(this->page % 2) {
		spriteBackground = SpriteUtil::create("fondo_ciudad.jpg", 0, 0, visibleSize.width, visibleSize.height);
	} else {
		spriteBackground = SpriteUtil::create("fondo_cementerio.jpg", 0, 0, visibleSize.width, visibleSize.height);
	}
	this->addChild(spriteBackground);

	//if first time, enable level 1
	if (DB::getInteger("level1", -1) == -1) {
		DB::putInteger("level1", 0);
	}

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
		LevelButton *button = new LevelButton(20*this->page + i+1, x, y);
		this->buttons.push_back(button);
		this->addChild(button->sprite);
		this->addChild(button->label);
	}

	y = ymargin;
	for (int i=0; i < 10 ;i++) {
		float x = xmargin + i * buttonWidth;
		LevelButton *button = new LevelButton(20*this->page + i+11, x, y);
		this->buttons.push_back(button);
		this->addChild(button->sprite);
		this->addChild(button->label);
	}

	cocos2d::CCSprite* prev = SpriteUtil::create("buttons/LEVELS-flechaIZ.png", 0,0);
	SpriteUtil::leftAlign((cocos2d::CCSprite*) this->buttons[0]->sprite, prev);
	prev->setPositionY(y - SpriteUtil::getHeight(prev) / 3);
	if(this->page > 0){
		this->prev = new LevelScreenButton(prev, this->page - 1);
		this->addChild(prev);
	}

	if(this->page < 4){
		cocos2d::CCSprite* next = SpriteUtil::create("buttons/LEVELS-flechaD.png", 0,y);
		SpriteUtil::rightAlign((cocos2d::CCSprite*) this->buttons[9]->sprite, next);
		next->setPositionY(prev->getPositionY());
		this->next = new LevelScreenButton(next, this->page + 1);
		this->addChild(next);
	}

	this->setTouchEnabled(true);
	return true;
}


void LevelSelectionLayer::ccTouchesBegan(cocos2d::CCSet *pTouches,
		cocos2d::CCEvent *pEvent) {

	if (this->touchId != 999) {
		CCLOG("Se abandona por touch ID");
		return;
	}

	cocos2d::CCSetIterator it = pTouches->begin();
	cocos2d::CCPoint location;
	cocos2d::CCTouch * touch;

	for (int iTouchCount = 0; iTouchCount < pTouches->count(); iTouchCount++) {

		touch = (cocos2d::CCTouch*) (*it);
		location = touch->getLocationInView();
		location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);
		this->touchId = touch->getID();

		this->beginLocation = this->lastLocation = location;
		it++;
	}
}

void LevelSelectionLayer::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {

	cocos2d::CCSetIterator it = pTouches->begin();
	cocos2d::CCPoint location;
	cocos2d::CCTouch * touch;

	for (int iTouchCount = 0; iTouchCount < pTouches->count(); iTouchCount++) {

		touch = (cocos2d::CCTouch*) (*it);
		location = touch->getLocationInView();
		location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

		if (this->touchId != touch->getID()) {
			continue;
		}

		float deltaX = location.x - lastLocation.x;
		float deltaY = location.y - lastLocation.y;
		lastLocation = location;

		it++;
	}
}

void LevelSelectionLayer::ccTouchesEnded(cocos2d::CCSet *pTouches,
		cocos2d::CCEvent *pEvent) {

	cocos2d::CCSetIterator it = pTouches->begin();
	cocos2d::CCPoint location;
	cocos2d::CCTouch * touch;

	for (int iTouchCount = 0; iTouchCount < pTouches->count(); iTouchCount++) {

		touch = (cocos2d::CCTouch*) (*it);
		location = touch->getLocationInView();
		location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

		if (this->touchId == touch->getID()) {
			CCLOG("Touch id renovado");
			this->touchId = 999;
		} else {
			continue;
		}

		float delta = location.x - beginLocation.x;
		float absDelta = delta;

		if (absDelta < 0) {
			absDelta *= -1;
		}

		if (absDelta < CLICK_MAX_DELTA) {
			cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
			cocos2d::CCPoint location = touch->getLocationInView();
			location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

			for (int i=0; i < this->buttons.size(); i++) {
				this->buttons[i]->touch(location);
			}

			if(this->page > 0){
				this->prev->touch(location);
			}

			if(this->page < 4){
				this->next->touch(location);
			}
		} else if (absDelta > 4 * CLICK_MAX_DELTA) {
			// move left or right

			if(this->page > 0 && delta > 0){
				this->prev->execute();
			}

			if(this->page < 4 && delta < 0){
				this->next->execute();
			}
		}
		it++;
	}
}

} /* namespace dxco */
