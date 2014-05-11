#include "ParallaxLayer.h"
#include "SpriteUtil.h"

namespace dxco {

ParallaxLayer::ParallaxLayer(std::string texture, float distance, int yPosition,
		bool repeat, int width, int height) {

	this->distance = distance;
	this->repeat = repeat;
	this->yPosition = yPosition;
	cocos2d::CCSprite* sprite = SpriteUtil::create(texture, 0, yPosition, width,
			height);

	this->width = SpriteUtil::getWidth(sprite);
	this->height = SpriteUtil::getHeight(sprite);

	sprites.push_back(sprite);
	cocos2d::CCSize visibleSize =
			cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	int cant = 0;

	if (repeat) {
		cant = (visibleSize.width / this->width) + 2;

		if (cant == 2) {
			cant = 3;
		}
	}

	for (int i = 0; i < cant; i++) {

		cocos2d::CCSprite* newSprite = SpriteUtil::create(texture,
				(i + 1) * this->width - 2, yPosition, width, height);

		this->sprites.push_back(newSprite);
	}
}

void ParallaxLayer::move(float deltaX, float deltaY) {

	if (this->distance > 9999) {
		return ;
	}

	float x = deltaX / this->distance;
	float y = deltaY / this->distance;

	if (this->repeat) {
		std::vector<cocos2d::CCSprite*> spritesToMove;

		for (int i = 0; i < this->sprites.size(); i++) {
			cocos2d::CCSprite* currSprite = this->sprites[i];
			SpriteUtil::move(currSprite, x, y);

			float offset = this->getOffset(currSprite);

			if (offset > (this->width / 2)) {
				spritesToMove.push_back(currSprite);
			}
		}

		cocos2d::CCSprite* lastSprite = this->getLastSprite();
		float xPos = lastSprite->getPosition().x + this->width;

		for (int i = 0; i < spritesToMove.size(); i++) {
			cocos2d::CCSprite* currSprite = spritesToMove[i];
			float xNewPos = xPos + (i * this->width) - 2;
			SpriteUtil::moveToAbsolute(currSprite, xNewPos, currSprite->getPositionY());
		}

	} else {
		SpriteUtil::move(this->sprites[0], x, y);
	}

}

void ParallaxLayer::restart() {
	for (int i = 0; i < this->sprites.size(); i++) {
		SpriteUtil::moveTo(this->sprites[i], (i * this->width) -2 , this->yPosition);
	}
}

float ParallaxLayer::getOffset(cocos2d::CCSprite* sprite) {
	float result = 0;

	if (sprite) {
		result = -(sprite->getPosition().x);
	}

	return result;
}

cocos2d::CCSprite* ParallaxLayer::getLastSprite() {

	int index = 0;

	for (int i = 1; i < this->sprites.size(); i++) {
		if (this->sprites[i]->getPosition().x
				> this->sprites[index]->getPosition().x) {
			index = i;
		}
	}

	return this->sprites[index];
}

ParallaxLayer::~ParallaxLayer() {

}

} /* namespace dxco */
