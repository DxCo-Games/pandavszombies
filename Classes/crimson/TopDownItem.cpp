#include "TopDownItem.h"

namespace dxco {

TopDownItem::TopDownItem(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int anglePositions) :
		Item(sprite, animations)  {

	this->anglePositions = anglePositions;
	this->rotation = 0;
	this->state = 0;
}

int TopDownItem::getState() {
	float angleRange = 360 / float(this->anglePositions);

	//add angleRange/2 so the ranges are centered around each anglePosition
	int angleState = - (this->rotation - angleRange / 2) / angleRange;
	if (angleState > 7) {
		angleState = 0;
	}

	return this->anglePositions * this->state + angleState;
}

float TopDownItem::getRotation() {
	return this->rotation;
}

void TopDownItem::setRotation(float rotation) {
	this->rotation = rotation;
}

} /* namespace dxco */
