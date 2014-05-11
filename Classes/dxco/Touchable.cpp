#include "Touchable.h"
#include "SpriteUtil.h"

namespace dxco {

Touchable::Touchable(cocos2d::CCNode* sprite) {
	this->sprite = sprite;
}

Touchable::~Touchable() {

}

cocos2d::CCNode* Touchable::getSprite() {
	return this->sprite;
}

void Touchable::on() {
	this->sprite->setVisible(true);
}

void Touchable::off() {
	this->sprite->setVisible(false);
}

void Touchable::touch(cocos2d::CCPoint location) {
	if (this->isTouched(location)) {
		this->execute();
	}
}

bool Touchable::isTouched(cocos2d::CCPoint location) {
	bool result = false;

	if (this->sprite) {
		result = this->sprite->isVisible() && this->sprite->boundingBox().containsPoint(location);
	}

	return result;
}


} /* namespace dxco */
