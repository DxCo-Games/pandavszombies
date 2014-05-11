#include "Container.h"

namespace dxco {

Container::Container(float x, float y, float width, float height) {
	this->setContentSize(cocos2d::CCSize(width, height));

	this->width = width;
	this->height = height;

	this->move(x, y);
}

float Container::getWidth() {
	return this->width;
}

float Container::getHeight() {
	return this->height;
}

void Container::move(float x, float y) {

	float xFinal = this->getPositionX() + x;
	float yFinal = this->getPositionY() + y;

	this->moveToAbsolute(xFinal, yFinal);
}

void Container::moveTo(float x, float y) {

	cocos2d::CCPoint origin =
						cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();

	float xFinal = x;
	float yFinal = y + this->getHeight() / 2;

	this->moveToAbsolute(xFinal + origin.x, yFinal + origin.y);
}

void Container::moveToAbsolute(float x, float y) {
	this->setPosition(ccp(x, y));
}

} /* namespace dxco */
