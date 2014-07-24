#include "TopDownItem.h"

namespace dxco {

TopDownItem::TopDownItem(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int anglePositions) :
		Item(sprite, animations)  {

	this->anglePositions = anglePositions;
	this->rotation = 0;
	this->state = 0;
}

int TopDownItem::getState() {
	int angleState = - this->rotation / float(360 / float(this->anglePositions));
	return this->anglePositions * this->state + angleState;
}

float TopDownItem::getRotation() {
	return this->rotation;
}

void TopDownItem::setRotation(float rotation) {
	this->rotation = rotation;
}

} /* namespace dxco */
