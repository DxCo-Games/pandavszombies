#include "EquipPandaItem.h"
#include "../../dxco/SpriteUtil.h"
#include "../../dxco/LabelUtil.h"
#include "cocos2d.h"

namespace dxco {


EquipPandaItem::EquipPandaItem(std::string item, float x, float y, float width, float height, cocos2d::CCSprite *master) : Container(x, y, width, height), Touchable(this) {
	this->item = item;

	cocos2d::CCSprite* background = SpriteUtil::create(this->getImagePath().c_str(), 0, height * 0.2, width, height * 0.8);
	SpriteUtil::copyScale(master, background);
	this->addChild(background);

	cocos2d::CCLabelTTF* nameLabel = LabelUtil::create(this->getName(), 18, 0, 0, 0, 0, "fonts/KBStickToThePlan.ttf");
	nameLabel->setAnchorPoint(ccp(0.5, 0.5));
	LabelUtil::setScaleByWidth(nameLabel, width * 0.5);

	cocos2d::CCPoint origin =
					cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();

	nameLabel->setPositionX(width * 0.5 + origin.x);
	nameLabel->setPositionY(height * 0.615 + origin.y);

	nameLabel->setColor(cocos2d::ccc3(62, 62, 62));

	this->addChild(nameLabel);

	cocos2d::CCSprite* coin = SpriteUtil::create("coin.png", width * 0.1, height * 0.25, width * 0.3, width * 0.3);
	SpriteUtil::copyScale(master, coin);
	this->addChild(coin);

	cocos2d::CCLabelTTF* coinsLabel = LabelUtil::create(this->_getPrice(), 18, 0, 0, 0, 0, "fonts/KBStickToThePlan.ttf");

	coinsLabel->setAnchorPoint(ccp(0.5, 0.5));
	LabelUtil::setScaleByHeight(nameLabel, width * 0.14);

	float coinsLabelWidth = LabelUtil::getWidth(coinsLabel);
	float coinsLabelHeight = LabelUtil::getHeight(coinsLabel);
	float nameLabelX = width * 0.1 + origin.x + SpriteUtil::getWidth(coin) + 17;
	float nameLabelY = height * 0.25 + origin.y + (coinsLabelHeight / 2);

	coinsLabel->setPositionX(nameLabelX);
	coinsLabel->setPositionY(nameLabelY);

	coinsLabel->setColor(cocos2d::ccc3(62, 62, 62));

	this->addChild(coinsLabel);

	cocos2d::CCSprite* buyButton = SpriteUtil::create(this->getBuyImagePath(), 0, 0, width, height * 0.15);
	SpriteUtil::copyScale(master, buyButton);
	this->addChild(buyButton);
}

std::string EquipPandaItem::getBuyImagePath() {
	return "buttons/BOTON-buy-activo.png";
}

std::string EquipPandaItem::getImagePath() {

	if (item == "BOMB") {
		return "equip/MEJORA_bomba_act.png";
	} else if (item == "SHOT") {
		return "equip/MEJORA_balas_act.png";
	} else {
		return "equip/MEJORA_bonus_act.png";
	}
}

std::string EquipPandaItem::getExplicacion() {
	return "Improve bomb explosion";
}

std::string EquipPandaItem::getName() {
	return this->item;
}

std::string EquipPandaItem::_getPrice() {
	return "500";
}

void EquipPandaItem::execute() {

}

} /* namespace dxco */
