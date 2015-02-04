#include "EquipPandaLayer.h"
#include "../../dxco/SpriteUtil.h"
#include "GameTypeSelectionLayer.h"
#include "../../dxco/Container.h"
#include <cstdlib>
#include "../../dxco/LabelUtil.h"
#include "../../dxco/StringUtil.h"
#include <string>
#include "EquipPandaItem.h"
#include "../GameProperties.h"

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
	cocos2d::CCPoint origin =
						cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	cocos2d::CCSprite* spriteBackground = SpriteUtil::create("fondo_ciudad.jpg", 0, 0, visibleSize.width, visibleSize.height);
	this->addChild(spriteBackground);


	float skillsPandaHeight = visibleSize.height * 0.72;
	float skillsPandaWidth = skillsPandaHeight * 0.5862;

	float xMargin = visibleSize.width * 0.05;
	float yMargin = (visibleSize.height - skillsPandaHeight) / 3;

	float skillsPandaX = xMargin;
	float skillsPandaY = yMargin;

	Container* skillsContainer = new Container(skillsPandaX, skillsPandaY, skillsPandaWidth, skillsPandaHeight);
	cocos2d::CCSprite* skillsPanda = SpriteUtil::create("equip/MEJORA_panda.png", 0, 0, skillsPandaWidth, skillsPandaHeight);
	skillsContainer->addChild(skillsPanda);
	this->addChild(skillsContainer, 10);

	this->createPandaItem(skillsPanda);

	cocos2d::CCSprite* spriteCoins = SpriteUtil::create("equip/coins.png", skillsPandaX,
														skillsPandaHeight * 1.1 + skillsPandaY - ((skillsPandaWidth * 0.34) / 2),
														skillsPanda);
//	SpriteUtil::leftAlign(skillsPanda, spriteCoins);
	this->addChild(spriteCoins);

	cocos2d::CCSprite* spriteGetCoinsButton = SpriteUtil::create("buttons/getcoins.png", 0, 0, skillsPanda);
	spriteGetCoinsButton->setPositionY(spriteCoins->getPositionY());
	spriteGetCoinsButton->setPositionX(visibleSize.width - SpriteUtil::getWidth(spriteGetCoinsButton) / 2 - xMargin);

	this->addChild(spriteGetCoinsButton);

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	std::string totalCoins = StringUtil::toString(this->getTotalCoins());
	cocos2d::CCLabelTTF* totalCoinsLabel = LabelUtil::create(totalCoins, 20, 0, 0, 0, 0, "fonts/KBStickToThePlan.ttf");
	LabelUtil::setScaleByHeight(totalCoinsLabel, skillsPandaWidth * 0.11);

	float labelTotalCoinsX = skillsPandaX + skillsPandaWidth * 0.35 + origin.x;
	float labelTotalCoinsY = spriteCoins->getPositionY();

	totalCoinsLabel->setAnchorPoint(ccp(0, 0.5));
	totalCoinsLabel->setPositionX(labelTotalCoinsX);
	totalCoinsLabel->setPositionY(labelTotalCoinsY);

	this->addChild(totalCoinsLabel);
	this->addSkills(skillsPandaX, skillsPandaY, skillsPandaWidth, skillsPandaHeight);

	this->touchId = 999;

	this->loadMejoras(skillsPandaWidth, skillsPandaHeight, skillsPandaX, skillsPandaY, skillsPanda);
	this->minX = items[0]->getPositionX() - skillsPandaWidth * 0.4;
	this->maxX = spriteGetCoinsButton->getPositionX() + SpriteUtil::getWidth(spriteGetCoinsButton) / 2;

	return true;
}

void EquipPandaLayer::createPandaItem(cocos2d::CCSprite* skillsPanda) {
	dxco::SpriteUtil::preloadTextureWithFile("sprite_sheets/panda1.plist");

	float pandaWidth = 0.85 * SpriteUtil::getWidth(skillsPanda);
	float pandaX = skillsPanda->getPositionX() - SpriteUtil::getWidth(skillsPanda) * 0.2;
	float pandaY = skillsPanda->getPositionY() + SpriteUtil::getHeight(skillsPanda) * 0.05;

	cocos2d::CCSprite* pandaSprite = SpriteUtil::create("caminata_15_0000.png", pandaX, pandaY, pandaWidth, pandaWidth, true);
	this->addChild(pandaSprite, 10);

	cocos2d::CCArray *animFrames = cocos2d::CCArray::createWithCapacity(14);

	for (int i=0; i <14; i++) {
		std::string index = "00" + StringUtil::toString(i);
		if (i < 10) {
			index = "0" + index;
		}
		animFrames->addObject(SpriteUtil::createSpriteFrame("caminata_15_" + index + ".png"));
	}

	cocos2d::CCAnimation *animation = cocos2d::CCAnimation::createWithSpriteFrames(animFrames, 0.05);
	cocos2d::CCAnimate* animate = cocos2d::CCAnimate::create(animation);
	pandaSprite->runAction(cocos2d::CCRepeatForever::create(animate));

}

void EquipPandaLayer::loadMejoras(float skillsPandaWidth, float skillsPandaHeight, float skillsPandaX, float skillsPandaY,
		cocos2d::CCSprite* scaleMaster) {

	std::vector<std::string> mejoras = EquipPandaItem::getMejoras();

	for (int i = 0; i < mejoras.size(); i++) {
		float itemsDeltaX = i * skillsPandaWidth * 0.85 + skillsPandaX + skillsPandaWidth * 1.15;
		EquipPandaItem* item = new EquipPandaItem(mejoras[i], itemsDeltaX, skillsPandaY, skillsPandaWidth * 0.8, skillsPandaHeight, scaleMaster);
		items.push_back(item);
		this->addChild(item);
	}
}

void EquipPandaLayer::addSkills(float skillsPandaX, float skillsPandaY, float skillsPandaWidth, float skillsPandaHeight) {
	this->addSkill(skillsPandaX, skillsPandaY, skillsPandaWidth, skillsPandaHeight, "life", this->getLife(), 0);
	this->addSkill(skillsPandaX, skillsPandaY, skillsPandaWidth, skillsPandaHeight, "attack", this->getAttack(), 1);
	this->addSkill(skillsPandaX, skillsPandaY, skillsPandaWidth, skillsPandaHeight, "speed", this->getSpeed(), 2);
	this->addSkill(skillsPandaX, skillsPandaY, skillsPandaWidth, skillsPandaHeight, "weapon time", this->getWeaponTime(), 3);
	this->addSkill(skillsPandaX, skillsPandaY, skillsPandaWidth, skillsPandaHeight, "bonus", this->getBonus(), 4);
}

void EquipPandaLayer::addSkill(float skillsPandaX, float skillsPandaY, float skillsPandaWidth, float skillsPandaHeight, std::string skillName, int skillValue, int index) {

	cocos2d::ccColor3B color = cocos2d::ccc3(62, 62, 62);
	float skillHeight = skillsPandaHeight * 0.05;
	std::string skillValueStr = StringUtil::toString(skillValue);
	cocos2d::CCPoint origin =
							cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();

	cocos2d::CCLabelTTF* skillsLabel = LabelUtil::create(skillName, 20, 0, 0, 0, 0, "fonts/KBStickToThePlan.ttf");
	cocos2d::CCLabelTTF* skillsLabelValue = LabelUtil::create(skillValueStr, 20, 0, 0, 0, 0, "fonts/KBStickToThePlan.ttf");

	float skillsLabelX = skillsPandaX + skillsPandaWidth * 0.1 + origin.x;
	float skillsLabelY = skillsPandaY + skillsPandaHeight * 0.5 + origin.y - (skillHeight * 0.8 * 2 * index);
	float skillsLabelValueX = skillsPandaX + skillsPandaWidth * 0.86 + origin.x;

	skillsLabel->setAnchorPoint(ccp(0, 0.5));
	skillsLabel->setColor(color);
	skillsLabel->setPositionX(skillsLabelX);
	skillsLabel->setPositionY(skillsLabelY);

	skillsLabelValue->setAnchorPoint(ccp(1, 0.5));
	skillsLabelValue->setColor(color);
	skillsLabelValue->setPositionX(skillsLabelValueX);
	skillsLabelValue->setPositionY(skillsLabelY);

	LabelUtil::setScaleByHeight(skillsLabel, skillHeight);
	LabelUtil::setScaleByHeight(skillsLabelValue, skillHeight);

	this->addChild(skillsLabel, 11);
	this->addChild(skillsLabelValue, 11);
}

void EquipPandaLayer::ccTouchesBegan(cocos2d::CCSet *pTouches,
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
		this->moved = 0.0;
		this->movingLeftAnimation = this->movingRigthAnimation = false;
		it++;
	}
}

void EquipPandaLayer::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {

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

		float itemWidth = SpriteUtil::getWidth((cocos2d::CCSprite*)items[0]->sprite);
		float firstX = items[0]->getPositionX() - itemWidth / 2 + deltaX;
		float lastX = items[items.size()-1]->getPositionX() + itemWidth + deltaX;

		if (firstX <= minX && lastX >= maxX) {
			for (int i = 0; i < items.size(); i++) {
				EquipPandaItem* item = items[i];

				item->move(deltaX, 0);
			}
		}

		it++;
	}
}



void EquipPandaLayer::ccTouchesEnded(cocos2d::CCSet *pTouches,
		cocos2d::CCEvent *pEvent) {

	cocos2d::CCSetIterator it = pTouches->begin();
	cocos2d::CCPoint location;
	cocos2d::CCTouch * touch;

	for (int iTouchCount = 0; iTouchCount < pTouches->count(); iTouchCount++) {

		touch = (cocos2d::CCTouch*) (*it);
		location = touch->getLocationInView();
		location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

		if (this->touchId == touch->getID()) {
			this->touchId = 999;
		} else {
			continue;
		}

		float delta = location.x - beginLocation.x;

		if (delta < 0) {
			delta *= -1;
		}

		if (delta < CLICK_MAX_DELTA) {
			for (int i = 0; i < this->items.size(); i++) {
				this->items[i]->touch(location);
			}
		} else {
			if (location.x - beginLocation.x > 0) {
				this->movingRigthAnimation = true;
			} else {
				this->movingLeftAnimation = true;
			}
		}
		it++;
	}

}

int EquipPandaLayer::getTotalCoins() {
	//FIXME use the correct number
	return rand() % 10000;
}

int EquipPandaLayer::getLife() {
	return GameProperties::get("player.life");
}

int EquipPandaLayer::getSpeed() {
	return GameProperties::get("player.speed");
}

int EquipPandaLayer::getAttack() {
	return GameProperties::get("bullet.damage");
}

int EquipPandaLayer::getWeaponTime() {
	return GameProperties::get("weapon.duration");
}

int EquipPandaLayer::getBonus() {
	return GameProperties::get("bonus.probability");
}

} /* namespace dxco */
