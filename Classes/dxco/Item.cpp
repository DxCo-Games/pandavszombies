#include "Item.h"

#include "SpriteUtil.h"
#include <map>
#include "MathUtil.h"

namespace dxco {

Item::Item(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) {
	this->sprite = sprite;
	this->state = 0;
	this->animations = animations;
	this->xInitial = sprite->getPositionX();
	this->yInitial = sprite->getPositionY();
	this->defaultTexture = sprite->getTexture();
}

void Item::update(float dt) {

	std::map<int, Animation*>::const_iterator itr = this->animations.find(this->getState());

	if (itr != this->animations.end()) {
		Animation* animation = itr->second;
		animation->update(this->sprite, dt);
	} else {
		this->sprite->setTexture(this->defaultTexture);
	}
}

void Item::updatePosition(float speed, float dt) {
	float offset = speed * dt;
	SpriteUtil::move(this->sprite, -offset, 0);
}


cocos2d::CCSprite* Item::getSprite() {
	return this->sprite;
}

void Item::restartPosition() {
	this->sprite->setPosition(ccp(this->xInitial, this->yInitial));
}

void Item::move(float deltaX, float deltaY) {
	SpriteUtil::move(this->sprite, deltaX, deltaY);
}

void Item::moveTo(float x, float y) {
	SpriteUtil::moveTo(this->sprite, x, y);
}

cocos2d::CCPoint Item::getLocation() {
	return this->sprite->getPosition();
}

int Item::getState() {
	return this->state;
}

float Item::getTopPosition() {
	return this->getLocation().y + this->getHeight() / 2;
}

float Item::getBottomPosition() {
	return this->getLocation().y - this->getHeight() / 2;
}

float Item::getLeftPosition() {
	return this->getLocation().x - this->getWidth() / 2;
}

float Item::getRightPosition() {
	return this->getLocation().x + this->getWidth() / 2;
}

float Item::getX() {
	return this->getLocation().x + (SpriteUtil::getWidth(this->sprite) / 2);
}

float Item::getY() {
	return this->getLocation().y - (SpriteUtil::getHeight(this->sprite) / 2);
}

float Item::getHeight() {
	return SpriteUtil::getHeight(this->sprite);
}

float Item::getWidth() {
	return SpriteUtil::getWidth(this->sprite);
}

void Item::goTo(cocos2d::CCPoint point, float distance) {
	float angle = MathUtil::angle(point, this->getLocation());

	this->move(cos(angle) * distance, sin(angle) * distance);
}

bool Item::collides(Item* item) {

	bool result = false;

	if (item && item->getSprite()) {
		item->getSprite()->getTextureRect().intersectsRect(this->getSprite()->getTextureRect());
	}

	return result;
}

bool Item::isOutOfScreen() {

	if (this->getRightPosition() < 0) {
		return true;
	}

	if (this->getTopPosition() < 0) {
		return true;
	}

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	if (this->getLeftPosition() > visibleSize.width) {
		return true;
	}

	if (this->getBottomPosition() > visibleSize.height) {
		return true;
	}

	return false;
}

} /* namespace dxco */
