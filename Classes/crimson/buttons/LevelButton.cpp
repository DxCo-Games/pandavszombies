#include "LevelButton.h"
#include "../../dxco/SpriteUtil.h"
#include "../../dxco/StringUtil.h"
#include "../../dxco/DB.h"
#include "../../HelloWorldScene.h"

namespace dxco {

LevelButton::LevelButton(int number, float x, float y) {
	this->number = number;

	int stars = DB::getInteger("level"+StringUtil::toString(number), -1);
	this->enabled = stars != -1;

	if (this->enabled) {
		this->sprite = SpriteUtil::create("buttons/LEVELS-x" + StringUtil::toString(stars) + ".png", x, y);
	} else {
		this->sprite = SpriteUtil::create("buttons/LEVELS-bloqueado.png", x, y);
	}
	this->on();

	std::string labelNumber = StringUtil::padLeft(number, 2);
	if(number == 100) {
		labelNumber = "?";
	}
	this->label = cocos2d::CCLabelTTF::create(labelNumber.c_str(), "fonts/KBStickToThePlan.ttf", 16);

	if (this->enabled) {
		this->label->setColor(cocos2d::ccc3(255, 255, 255));
	} else {
		this->label->setColor(cocos2d::ccc3(145, 12, 28));
	}

	float height = SpriteUtil::getHeight((cocos2d::CCSprite*)this->sprite);
	float width = SpriteUtil::getWidth((cocos2d::CCSprite*)this->sprite);
	this->label->setPositionX(this->sprite->getPositionX() - 0.03*width);
	this->label->setPositionY(this->sprite->getPositionY() + 0.29*height);
}

void LevelButton::execute() {
	if (this->enabled) {
		cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
		pDirector->replaceScene(HelloWorld::scene(false, this->number));
	}
}


} /* namespace dxco */
