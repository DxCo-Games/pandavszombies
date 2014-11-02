#include "EquipPandaLayer.h"
#include "../../dxco/SpriteUtil.h"
#include "GameTypeSelectionLayer.h"

namespace dxco {

cocos2d::CCScene* EquipPandaLayer::scene() {

	cocos2d::CCScene *scene = cocos2d::CCScene::create();
	EquipPandaLayer* layer = new EquipPandaLayer();

	layer->init();
	scene->addChild(layer);

	return scene;
}

bool EquipPandaLayer::init() {
	if (!cocos2d::CCLayer::init()) {
		return false;
	}

	std::vector<std::string> mejoras;

	mejoras.push_back("BOMB");
	mejoras.push_back("SHOT");
	mejoras.push_back("BONUS");
	mejoras.push_back("BOMB");
	mejoras.push_back("SHOT");
	mejoras.push_back("BONUS");
	mejoras.push_back("BOMB");
	mejoras.push_back("SHOT");
	mejoras.push_back("BONUS");

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	cocos2d::CCSprite* spriteBackground = SpriteUtil::create("fondo_ciudad.jpg", 0, 0, visibleSize.width, visibleSize.height);
	this->addChild(spriteBackground);

	float xMargin = visibleSize.width * 0.05;

	float skillsPandaHeight = visibleSize.height * 0.6;
	float skillsPandaWidth = skillsPandaHeight * 0.58;
	float skillsPandaX = xMargin;
	float skillsPandaY = (visibleSize.height - skillsPandaHeight) / 2;
	cocos2d::CCSprite* skillsPanda = SpriteUtil::create("equip/MEJORA_panda.png", skillsPandaX, skillsPandaY, skillsPandaWidth, skillsPandaHeight);
	this->addChild(skillsPanda, 10);

	cocos2d::CCSprite* spriteCoins = SpriteUtil::create("equip/coins.png", 0, 0);
	SpriteUtil::leftAlign(skillsPanda, spriteCoins);
	spriteCoins->setPositionY(visibleSize.height * 0.95);
	this->addChild(spriteCoins);

	cocos2d::CCSprite* spriteGetCoinsButton = SpriteUtil::create("buttons/getcoins.png", 0,0);
	SpriteUtil::copyScale(spriteCoins, spriteGetCoinsButton);
	spriteGetCoinsButton->setPositionY(spriteCoins->getPositionY());
	spriteGetCoinsButton->setPositionX(visibleSize.width - SpriteUtil::getWidth(spriteGetCoinsButton) - xMargin);
	this->addChild(spriteGetCoinsButton);

	for (int i = 0; i < mejoras.size(); i++) {
		float itemsDeltaX = i * skillsPandaWidth + skillsPandaX + skillsPandaWidth * 1.2;
		EquipPandaItem* item = new EquipPandaItem(mejoras[i], itemsDeltaX, skillsPandaY, skillsPandaWidth * 0.8, skillsPandaHeight, skillsPanda);
		items.push_back(item);
		this->addChild(item);
	}

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	return true;
}


void EquipPandaLayer::ccTouchesBegan(cocos2d::CCSet *pTouches,
		cocos2d::CCEvent *pEvent) {

	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());

	cocos2d::CCPoint location = touch->getLocationInView();
	location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

	this->beginLocation = this->lastLocation = location;
	this->moved = 0.0;
	this->movingLeftAnimation = this->movingRigthAnimation = false;
}

void EquipPandaLayer::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {

	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
	cocos2d::CCPoint location = touch->getLocationInView();
	location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

	float deltaX = location.x - lastLocation.x;
	float deltaY = location.y - lastLocation.y;
	lastLocation = location;

	for (int i = 0; i < items.size(); i++) {
		EquipPandaItem* item = items[i];

		item->move(deltaX, 0);
	}
	//this->moveItems(deltaX);
}

void EquipPandaLayer::ccTouchesEnded(cocos2d::CCSet *pTouches,
		cocos2d::CCEvent *pEvent) {

	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
	cocos2d::CCPoint location = touch->getLocationInView();
	location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

	float delta = location.x - beginLocation.x;

	if (delta < 0) {
		delta *= -1;
	}

	if (delta < CLICK_MAX_DELTA) {

	} else {
		if (location.x - beginLocation.x > 0) {
			this->movingRigthAnimation = true;
		} else {
			this->movingLeftAnimation = true;
		}
	}
}

void EquipPandaLayer::keyBackClicked() {
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->replaceScene(GameTypeSelectionLayer::scene());
}

} /* namespace dxco */
