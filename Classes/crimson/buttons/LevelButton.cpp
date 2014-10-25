#include "LevelButton.h"
#include "../../dxco/SpriteUtil.h"
#include "../../dxco/StringUtil.h"

namespace dxco {

LevelButton::LevelButton(int number, float x, float y) {
	this->number = number;

	//TODO if level not in db then not enabled
	//TODO if level in db get stars
	this->sprite = SpriteUtil::create("buttons/LEVELS-x0.png", x, y);
	this->on();

	this->label = cocos2d::CCLabelTTF::create(StringUtil::padLeft(number, 2).c_str(), "fonts/KBStickToThePlan.ttf", 17);
	this->label->setColor(cocos2d::ccc3(255, 255, 255));

	float height = SpriteUtil::getHeight((cocos2d::CCSprite*)this->sprite);
	float width = SpriteUtil::getWidth((cocos2d::CCSprite*)this->sprite);
	this->label->setPositionX(this->sprite->getPositionX() - 0.03*width);
	this->label->setPositionY(this->sprite->getPositionY() + 0.29*height);
}

void LevelButton::execute() {
	//TODO call hello world in mode story with given level number
}


} /* namespace dxco */
