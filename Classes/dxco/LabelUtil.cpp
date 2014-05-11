#include "LabelUtil.h"
#include "SpriteUtil.h"
namespace dxco {

cocos2d::CCLabelTTF* LabelUtil::create(std::string text, int fontSize, int x,
		int y, int vertical, int horizontal, cocos2d::CCSprite* sprite) {
	float width = SpriteUtil::getWidth(sprite);
	float height = SpriteUtil::getHeight(sprite);

	cocos2d::CCPoint origin = sprite->getPosition();

	return LabelUtil::create(text, fontSize, x, y, vertical, horizontal, width,
			height, origin);
}

cocos2d::CCLabelTTF* LabelUtil::create(std::string text, int fontSize, int x,
		int y, int vertical, int horizontal) {

	cocos2d::CCSize visibleSize =
			cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	float width = visibleSize.width;
	float height = visibleSize.height;
	cocos2d::CCPoint origin =
			cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();

	return LabelUtil::create(text, fontSize, x, y, vertical, horizontal, width,
			height, origin);
}

cocos2d::CCLabelTTF* LabelUtil::create(std::string text, int fontSize, int x,
		int y, int vertical, int horizontal, float width, float height,
		cocos2d::CCPoint origin) {
	return create(text, fontSize, x, y, vertical, horizontal, width, height,
			origin, "fonts/MarkerFelt.ttf");
}

cocos2d::CCLabelTTF* LabelUtil::create(std::string text, int fontSize, int x,
		int y, int vertical, int horizontal, float width, float height,
		cocos2d::CCPoint origin, std::string font) {

	cocos2d::CCLabelTTF* result = cocos2d::CCLabelTTF::create(text.c_str(),
			font.c_str(), fontSize);

	float x_position;
	float anchor_point_x;

	float y_position;
	float anchor_point_y;

	if (horizontal == LEFT) {
		x_position = x;
		anchor_point_x = 0;
	} else {
		x_position = width - x;
		anchor_point_x = 1;
	}

	if (vertical == TOP) {
		y_position = height - y;
		anchor_point_y = 1;
	} else if (vertical == MIDDLE) {
		y_position = (height / 2) + y + (fontSize / 2);
		x_position = (width / 2) + x;
		anchor_point_y = 0.5;
		anchor_point_x = 0.5;
	} else {
		y_position = y;
		anchor_point_y = 0;
	}

	result->setAnchorPoint(ccp(anchor_point_x,anchor_point_y));
	result->setPosition(ccp(x_position + origin.x, y_position + origin.y));
	return result;
}

void LabelUtil::move(cocos2d::CCLabelTTF* label, float deltaX, float deltaY) {

	if (label) {
		float xPos, yPos;
		float newX, newY;

		label->getPosition(&xPos, &yPos);

		newX = xPos + deltaX;
		newY = yPos + deltaY;

		label->setPosition(ccp(newX, newY));
	}
}

void LabelUtil::moveTo(cocos2d::CCLabelTTF* label, float x, float y) {
	if (label) {
		cocos2d::CCPoint origin =
				cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
		label->setPosition(
				ccp(origin.x + x + LabelUtil::getWidth(label) / 2, origin.y + y + LabelUtil::getHeight(label) / 2));
			}
		}

void LabelUtil::moveToAbsolute(cocos2d::CCLabelTTF* label, float x, float y) {
	if (label) {
		label->setPositionX(x);
		label->setPositionY(y);
	}
}

float LabelUtil::getXMiddle(cocos2d::CCLabelTTF* label) {
	float result = 0;

	if (label) {

	}

	return result;
}
float LabelUtil::getWidth(cocos2d::CCLabelTTF* label) {
	float result = 0;

	if (label) {
		result = label->getContentSize().width * label->getScaleX();
	}

	return result;
}

float LabelUtil::getHeight(cocos2d::CCLabelTTF* label) {
	float result = 0;

	if (label) {
		result = label->getContentSize().height * label->getScaleY();
	}

	return result;
}

void LabelUtil::setColor(cocos2d::CCLabelTTF* label, int color) {

	if (label) {
		if (color == WHITE) {
			label->setColor(cocos2d::ccc3(255, 255, 255));
		} else if (color == BLACK) {
			label->setColor(cocos2d::ccc3(0, 0, 0));
		} else if (color == BLUE) {
			label->setColor(cocos2d::ccc3(0, 0, 255));
		} else if (color == GREEN) {
			label->setColor(cocos2d::ccc3(0, 255, 9));
		} else if (color == RED) {
			label->setColor(cocos2d::ccc3(255, 0, 0));
		} else if (color == GREY) {
			label->setColor(cocos2d::ccc3(84, 84, 84));
		} else if (color == BROWN) {
			label->setColor(cocos2d::ccc3(165, 42, 42));
		} else if (color == PINK) {
			label->setColor(cocos2d::ccc3(255, 192, 203));
		} else if (color == PURPLE) {
			label->setColor(cocos2d::ccc3(160, 32, 240));
		} else if (color == YELLOW) {
			label->setColor(cocos2d::ccc3(255, 255, 0));
		} else if (color == GOLD) {
			label->setColor(cocos2d::ccc3(255, 215, 0));
		}
	}
}

} /* namespace dxco */
