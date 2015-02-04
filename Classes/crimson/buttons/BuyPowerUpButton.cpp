#include "BuyPowerUpButton.h"
#include "../layers/EquipPandaItem.h"

namespace dxco {

BuyPowerUpButton::BuyPowerUpButton(cocos2d::CCSprite* sprite, EquipPandaItem* item) : ButtonDxCo(sprite) {
	this->on();
	this->item = item;
}

void BuyPowerUpButton::execute() {
	item->applyPowerUp();
}

} /* namespace dxco */
