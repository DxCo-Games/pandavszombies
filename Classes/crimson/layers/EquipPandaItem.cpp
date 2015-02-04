#include "EquipPandaItem.h"
#include "EquipPandaLayer.h"
#include "../../dxco/SpriteUtil.h"
#include "../../dxco/LabelUtil.h"
#include "../../dxco/StringUtil.h"
#include "../GameProperties.h"
#include "../buttons/BuyPowerUpButton.h"
#include "cocos2d.h"

#include <cstdlib>

namespace dxco {

EquipPandaItem::EquipPandaItem(std::string item, float x, float y, float width,
		float height,cocos2d::CCSprite* scaleMaster) :
		Container(x, y, width, height) {
	this->item = item;
	this->price = 0;

	cocos2d::CCSprite* background = SpriteUtil::create(
			this->getImagePath().c_str(), 0, height * 0.2, scaleMaster);
	SpriteUtil::topAlign(scaleMaster, background);
	this->addChild(background);

	cocos2d::CCLabelTTF* nameLabel = LabelUtil::create(this->getName(), 19, 0,
			0, 0, 0, "fonts/KBStickToThePlan.ttf");
	nameLabel->setAnchorPoint(ccp(0.5, 0.5));
	LabelUtil::setScaleByWidth(nameLabel, width * 0.5);

	cocos2d::CCPoint origin =
			cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();

	nameLabel->setPositionX(width * 0.52 + origin.x);
	nameLabel->setPositionY(height * 0.59 + origin.y);

	nameLabel->setColor(cocos2d::ccc3(62, 62, 62));

	this->addChild(nameLabel);

	cocos2d::CCLabelTTF* detailLabel = cocos2d::CCLabelTTF::create(this->getDetail().c_str(), "fonts/KBStickToThePlan.ttf",
			10, cocos2d::CCSize(85,0), cocos2d::kCCTextAlignmentCenter);

	detailLabel->setPositionX(nameLabel->getPositionX());
	detailLabel->setPositionY(height * 0.43 + origin.y);
	detailLabel->setColor(cocos2d::ccc3(62, 62, 62));
	this->addChild(detailLabel);


	cocos2d::CCSprite* coin = SpriteUtil::create("coin.png", width * 0.09,
			height * 0.22, scaleMaster);
	this->addChild(coin);

	cocos2d::CCLabelTTF* coinsLabel = LabelUtil::create(StringUtil::toString(this->getPrice()), 13,
			0, 0, 0, 0, "fonts/KBStickToThePlan.ttf");

	coinsLabel->setAnchorPoint(ccp(0.5, 0.5));
	LabelUtil::setScaleByHeight(nameLabel, width * 0.12);

	float coinsLabelWidth = LabelUtil::getWidth(coinsLabel);
	float coinsLabelHeight = LabelUtil::getHeight(coinsLabel);

	float nameLabelX = width * 0.14 + origin.x + SpriteUtil::getWidth(coin) + 17;
	float nameLabelY = coin->getPositionY();

	coinsLabel->setPositionX(nameLabelX);
	coinsLabel->setPositionY(nameLabelY);

	coinsLabel->setColor(cocos2d::ccc3(62, 62, 62));

	this->addChild(coinsLabel);

	std::string cantidadStr = StringUtil::toString(
			this->getCantidadDisponible());

	cocos2d::CCLabelTTF* cantidadLabel = LabelUtil::create(cantidadStr, 18, 0,
			0, 0, 0, "fonts/KBStickToThePlan.ttf");

	LabelUtil::setScaleByHeight(cantidadLabel, width * 0.15);

	float cantidadLabelHeight = LabelUtil::getHeight(cantidadLabel);
	float cantidadLabelWidth = LabelUtil::getWidth(cantidadLabel);

	float cantidadLabelX = (cantidadLabelWidth / 2) + origin.x + width * 0.17;
	float cantidadLabelY = height - (cantidadLabelHeight / 2) + origin.y
			- width * 0.19;

	cantidadLabel->setPositionX(cantidadLabelX);
	cantidadLabel->setPositionY(cantidadLabelY);

	if (!this->isActivo()) {
		cantidadLabel->setColor(cocos2d::ccc3(181, 181, 181));
	}

	this->addChild(cantidadLabel);

	cocos2d::CCSprite* buyButton = SpriteUtil::create(this->getBuyImagePath(),
			0, 0, scaleMaster);
	SpriteUtil::bottomAlign(scaleMaster, buyButton);
	buyButton->setPositionX(background->getPositionX());
	this->addChild(buyButton);
	this->button = new BuyPowerUpButton(buyButton, this);

}


int EquipPandaItem::getCantidadDisponible() {

	int result = 5;

	if (this->item == "bazooka.unlocked" || this->item == "fire.unlocked" || this->item == "firebullet.unlocked") {
		if (GameProperties::get(this->item)) {
			result = 0;
		} else {
			result = 1;
		}
	//FIXME sacar la opcion despues de desbloquear. El damage se mejora en conjunto con las otras armas
	} else if (this->item == "bazooka.damage") {
		if (!GameProperties::get("bazooka.unlocked")) {
			// si todavia no destrabamos la bazooka no podemos mejorarla.
			return 0;
		} else {
			result = GameProperties::get("bazooka.damage.level");
		}
	} else {
		result = GameProperties::get(this->item + std::string(".level"));
	}

	return result;
}

bool EquipPandaItem::isActivo() {
	return getCantidadDisponible() > 0;
}

std::vector<std::string> EquipPandaItem::getMejoras() {

	std::vector<std::string> mejoras;


	mejoras.push_back("player.life");
	mejoras.push_back("player.speed");
	mejoras.push_back("bonus.probability");

	mejoras.push_back("weapon.duration");
	mejoras.push_back("bullet.damage");
	//mejorar todos los damages juntos (propiedad attack del panda)
//	mejoras.push_back("bazooka.damage");
//	mejoras.push_back("explosion.damage");

	mejoras.push_back("firebullet.unlocked");
	mejoras.push_back("bazooka.unlocked");
	mejoras.push_back("fire.unlocked");

	return mejoras;
}

std::string EquipPandaItem::getBuyImagePath() {
	if (this->isActivo()) {
		return "buttons/buy.png";
	}

	return "buttons/buy-inactivo.png";
}


std::string EquipPandaItem::getImagePath() {

	std::string result = "equip/MEJORA_";

	if (this->item == "bazooka.unlocked") {
		result.append("bazooka");
	} else if (this->item == "fire.unlocked") {
		result.append("fuego");
	} else if (this->item == "firebullet.unlocked") {
		result.append("fuego");
	} else if (this->item == "player.life") {
		result.append("energia");
	} else if (this->item == "player.speed") {
		result.append("velocidad");
	} else if (this->item == "bonus.probability") {
		result.append("regalo");
	} else if (this->item == "weapon.duration") {
		result.append("reloj");
	} else if (this->item == "bullet.damage") {
		result.append("balasv");
//	} else if (this->item == "bazooka.damage") {
//		result.append("bazooka");
//	} else if (this->item == "explosion.damage") {
//		result.append("bomba");
	}

	if (this->isActivo()) {
		result.append("_act.png");
	} else {
		result.append("_desac.png");
	}

	return result;
}

std::string EquipPandaItem::getExplicacion() {
	return "Improve bomb explosion";
}

std::string EquipPandaItem::getName() {

	if (this->item == "bazooka.unlocked") {
		return "BAZOOKA";
	} else if (this->item == "fire.unlocked") {
		return "FLAME";
	} else if (this->item == "firebullet.unlocked") {
		return "FIREBALL";
	} else if (this->item == "player.life") {
		return "LIFE";
	} else if (this->item == "player.speed") {
		return "SPEED";
	} else if (this->item == "bonus.probability") {
		return "BONUS %";
	} else if (this->item == "weapon.duration") {
		return "WEAPON";
	} else if (this->item == "bullet.damage") {
		return "ATTACK";
//	} else if (this->item == "bazooka.damage") {
//		return "Bazooka";
//	} else if (this->item == "explosion.damage") {
//		return "Bomb";
	}

	return " ";
}

std::string EquipPandaItem::getDetail() {
	if (this->item == "bazooka.unlocked") {
		return "unlock the bazooka";
	} else if (this->item == "fire.unlocked") {
		return "unlock the flamethrower";
	} else if (this->item == "firebullet.unlocked") {
		return "unlock the fireballs";
	} else if (this->item == "player.life") {
		return "10% life increase";
	} else if (this->item == "player.speed") {
		return "2% speed increase";
	} else if (this->item == "bonus.probability") {
		return "2% bonus frequency increase";
	} else if (this->item == "weapon.duration") {
		return "10% weapon duration increase";
	} else if (this->item == "bullet.damage") {
		return "10% attack increase";
	}
	return " ";
}

int EquipPandaItem::getPrice() {
	return GameProperties::getPrice(this->item);
}

void EquipPandaItem::applyPowerUp() {

	CCLOG("Upgrade item %s", this->item.c_str());

	if (this->isActivo()) {
		CCLOG("Upgrade item %s active", this->item.c_str());
		GameProperties::powerUp(this->item);

		cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
		//TODO reload scene, hay alguna forma mejor de hacerlo?
		pDirector->popScene();
		pDirector->pushScene(EquipPandaLayer::scene());
	}
}

} /* namespace dxco */
