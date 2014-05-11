#include "Joystick.h"

namespace dxco {

Joystick::Joystick(cocos2d::CCSprite* sprite, float radio) {
	this->sprite = sprite;
	this->center = sprite->getPosition();
	this->radio = radio;
}


void Joystick::onMoved(cocos2d::CCPoint location, float angle, float intensity) {
	this->sprite->setPosition(location);
}

void Joystick::onTouchedBegan(cocos2d::CCPoint location, float angle, float intensity) {
	this->sprite->setPosition(location);
}


void Joystick::onTouchedEnded(cocos2d::CCPoint location, float angle, float intensity) {
	this->sprite->setPosition(this->center);
}

cocos2d::CCPoint Joystick::getCenter() {
	return this->center;
}

float Joystick::getRadio() {
	return this->radio;
}

} /* namespace dxco */
