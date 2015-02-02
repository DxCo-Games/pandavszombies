#include "RankingLayer.h"

#include "../../dxco/SpriteUtil.h"

namespace dxco {

cocos2d::CCScene* RankingLayer::scene() {

	cocos2d::CCScene* scene = cocos2d::CCScene::create();
	RankingLayer* layer = new RankingLayer();

	layer->init();
	scene->addChild(layer);

	return scene;
}

bool RankingLayer::init() {
	if (!cocos2d::CCLayer::init()) {
		return false;
	}

	// this->setTouchEnabled(true);
	// this->setKeypadEnabled(true);

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	cocos2d::CCSprite* spriteBackground = SpriteUtil::create("fondo_ciudad.jpg", 0, 0, visibleSize.width, visibleSize.height);
	this->addChild(spriteBackground);

	cocos2d::CCSprite* title = SpriteUtil::create("ranking_title.png", visibleSize.width * 0.2, visibleSize.height * 0.78, visibleSize.width * 0.6, visibleSize.height * 0.15);
	this->addChild(title);

	int posicionX = visibleSize.width * 0.21;

	cocos2d::CCSprite* friendsButtonActive = SpriteUtil::create("buttons/friends_button_active.png", posicionX, visibleSize.height * 0.65, title);
	this->addChild(friendsButtonActive);

	cocos2d::CCSprite* rankingPosition = SpriteUtil::create("ranking_position.png", visibleSize.width * 0.2, visibleSize.height * 0.45, title);
	this->addChild(rankingPosition);

	cocos2d::CCSprite* placaPosicion = SpriteUtil::create("posicion_ranking_copa.png", posicionX + visibleSize.width * 0.08, visibleSize.height * 0.45, title);
	this->addChild(placaPosicion);

	cocos2d::CCSprite* fotoCargado = SpriteUtil::create("ranking_foto_cargando.png", posicionX + visibleSize.width * 0.09, visibleSize.height * 0.49, title);
	this->addChild(fotoCargado);

	return true;
}

void RankingLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
}

void RankingLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
}

} /* namespace dxco */
