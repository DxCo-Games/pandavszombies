#include "EquipPandaLayer.h"
#include "../../dxco/SpriteUtil.h"
#include "GameTypeSelectionLayer.h"
#include "EquipPandaSkillsContainer.h"
#include <cstdlib>
#include "../../dxco/LabelUtil.h"
#include "../../dxco/StringUtil.h"
#include <string>

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

	EquipPandaSkillsContainer* skillsContainer = new EquipPandaSkillsContainer(skillsPandaX, skillsPandaY, skillsPandaWidth, skillsPandaHeight);
	this->addChild(skillsContainer, 10);

	cocos2d::CCSprite* spriteCoins = SpriteUtil::create("equip/coins.png", skillsPandaX,
														skillsPandaHeight * 1.1 + skillsPandaY - ((skillsPandaWidth * 0.34) / 2),
														skillsPandaWidth, skillsPandaWidth * 0.34);
	this->addChild(spriteCoins);

	cocos2d::CCSprite* spriteGetCoinsButton = SpriteUtil::create("buttons/getcoins.png", visibleSize.width * 0.9 - skillsPandaWidth,
														skillsPandaHeight * 1.1 + skillsPandaY - ((skillsPandaWidth * 0.34) / 2),
														skillsPandaWidth, skillsPandaWidth * 0.34);

	this->addChild(spriteGetCoinsButton);

	for (int i = 0; i < mejoras.size(); i++) {
		float itemsDeltaX = i * skillsPandaWidth * 0.85 + skillsPandaX + skillsPandaWidth * 1.15;
		EquipPandaItem* item = new EquipPandaItem(mejoras[i], itemsDeltaX, skillsPandaY, skillsPandaWidth * 0.8, skillsPandaHeight);
		items.push_back(item);
		this->addChild(item);
	}

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	std::string totalCoins = StringUtil::toString(this->getTotalCoins());

	cocos2d::CCLabelTTF* totalCoinsLabel = LabelUtil::create(totalCoins, 20, 0, 0, 0, 0);
	cocos2d::CCPoint origin =
					cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();

	LabelUtil::setScaleByHeight(totalCoinsLabel, skillsPandaWidth * 0.15);

	float labelTotalCoinsX = skillsPandaX + skillsPandaWidth * 0.35 + origin.x;
	float labelTotalCoinsY = spriteCoins->getPositionY();

	totalCoinsLabel->setAnchorPoint(ccp(0, 0.5));
	totalCoinsLabel->setPositionX(labelTotalCoinsX);
	totalCoinsLabel->setPositionY(labelTotalCoinsY);

	this->addChild(totalCoinsLabel);

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

int EquipPandaLayer::getTotalCoins() {
	return rand() % 10000;
}

} /* namespace dxco */
