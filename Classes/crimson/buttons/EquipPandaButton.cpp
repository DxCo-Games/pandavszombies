#include "EquipPandaButton.h"

#include "../layers/EquipPandaLayer.h"

namespace dxco {

EquipPandaButton::EquipPandaButton(cocos2d::CCSprite* sprite) : ButtonDxCo(sprite) {
	this->on();
}

void EquipPandaButton::execute() {
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->pushScene(EquipPandaLayer::scene());
}

} /* namespace dxco */
