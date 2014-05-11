#include "Animation.h"

namespace dxco {

Animation::Animation(std::vector<cocos2d::CCTexture2D*> textures, float frameTime, bool repeat) {
	this->textures = textures;
	this->frameTime = frameTime;
	this->repeat = repeat;
	this->dt = 0;
	this->index = 0;
	this->finished = false;
}

void Animation::restart() {
	this->finished = false;
	this->index = 0;
	this->dt = 0;
}

void Animation::update(cocos2d::CCSprite* sprite, float dt) {

	this->dt += dt;

	if (this->dt > this->frameTime) {
		this->dt = 0;
		this->index++;
	}

	if (this->index >= this->textures.size()) {
		if (this->repeat) {
			this->index = 0;
		} else {
			this->finished = true;
			this->index = this->textures.size() - 1;
		}
	}

	cocos2d::CCTexture2D* texture = (cocos2d::CCTexture2D*) this->textures[this->index];
	sprite->setTexture(texture);
}

} /* namespace dxco */
