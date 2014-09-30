#include "GameTypeSelectionLayer.h"

#include "../../dxco/SpriteUtil.h"

namespace dxco {

GameTypeSelectionLayer::GameTypeSelectionLayer() {

}

bool GameTypeSelectionLayer::init() {
	if (!cocos2d::CCLayer::init()) {
		return false;
	}

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	cocos2d::CCSprite* spriteBackground = SpriteUtil::create("ciudad_fondo.png", 0, 0, visibleSize.width, visibleSize.height);
	this->addChild(spriteBackground);

	this->setTouchEnabled(true);

	return true;
}

cocos2d::CCScene* GameTypeSelectionLayer::scene() {

	cocos2d::CCScene *scene = cocos2d::CCScene::create();
	GameTypeSelectionLayer* layer = new GameTypeSelectionLayer();

	layer->init();
	scene->addChild(layer);

	return scene;
}

} /* namespace dxco */
