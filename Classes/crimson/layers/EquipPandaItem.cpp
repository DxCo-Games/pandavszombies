#include "EquipPandaItem.h"
#include "../../dxco/SpriteUtil.h"
#include "../../dxco/LabelUtil.h"
#include "../../dxco/StringUtil.h"
#include "cocos2d.h"

#include <cstdlib>

namespace dxco {


EquipPandaItem::EquipPandaItem(std::string item, float x, float y, float width, float height, cocos2d::CCSprite *master) : Container(x, y, width, height), Touchable(this) {
	this->item = item;
	this->cantidadDisponible = rand() % 2;

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

	std::string cantidadStr = StringUtil::toString(this->getCantidadDisponible());

	cocos2d::CCLabelTTF* cantidadLabel = LabelUtil::create(cantidadStr, 18, 0, 0, 0, 0, "fonts/KBStickToThePlan.ttf");

	cantidadLabel->setAnchorPoint(ccp(0.5, 0.5));
	LabelUtil::setScaleByHeight(cantidadLabel, width * 0.15);

	float cantidadLabelHeight = LabelUtil::getHeight(cantidadLabel);
	float cantidadLabelWidth = LabelUtil::getWidth(cantidadLabel);

	float cantidadLabelX = (cantidadLabelWidth / 2) + origin.x + width * 0.09;
	float cantidadLabelY = height - (cantidadLabelHeight / 2) + origin.y - width * 0.072;

	cantidadLabel->setPositionX(cantidadLabelX);
	cantidadLabel->setPositionY(cantidadLabelY);

	if (!this->isActivo()) {
		cantidadLabel->setColor(cocos2d::ccc3(181, 181, 181));
	}

	this->addChild(cantidadLabel);

	cocos2d::CCSprite* buyButton = SpriteUtil::create(this->getBuyImagePath(), 0, 0, width, height * 0.15);
	SpriteUtil::copyScale(master, buyButton);
	this->addChild(buyButton);
}

bool EquipPandaItem::isActivo() {
	return this->cantidadDisponible > 0;
}

std::string EquipPandaItem::getBuyImagePath() {
	if (this->isActivo()) {
		return "buttons/buy.png";
	}

	return "buttons/buy-inactivo.png";
}

int EquipPandaItem::getCantidadDisponible() {
	return this->cantidadDisponible;
}

std::string EquipPandaItem::getImagePath() {

	if (item == "BOMB") {

		if (this->isActivo()) {
			return "equip/MEJORA_bomba_act.png";
		} else {
			return "equip/MEJORA_bomba_desac.png";
		}
	} else if (item == "SHOT") {
		if (this->isActivo()) {
			return "equip/MEJORA_balas_act.png";
		} else {
			return "equip/MEJORA_balas_desac.png";
		}
	} else {
		if (this->isActivo()) {
			return "equip/MEJORA_bonus_act.png";
		} else {
			return "equip/MEJORA_bonus_desac.png";
		}
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

	if (this->isActivo()) {
		// TODO equip
	}
}

} /* namespace dxco */
