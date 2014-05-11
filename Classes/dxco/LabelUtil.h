#ifndef LABELUTIL_H_
#define LABELUTIL_H_

#include "cocos2d.h"
#include <string>

namespace dxco {

class LabelUtil {
public:
	static cocos2d::CCLabelTTF* create(std::string text,  int fontSize, int x, int y, int vertical, int horizontal);
	static cocos2d::CCLabelTTF* create(std::string text,  int fontSize, int x, int y, int vertical, int horizontal, cocos2d::CCSprite* sprite);
	static cocos2d::CCLabelTTF* create(std::string text,  int fontSize, int x, int y, int vertical, int horizontal, float width, float height, cocos2d::CCPoint origin);
	static cocos2d::CCLabelTTF* create(std::string text,  int fontSize, int x, int y, int vertical, int horizontal, float width, float height, cocos2d::CCPoint origin, std::string font);

	static void setColor(cocos2d::CCLabelTTF* label, int color);
	static void move(cocos2d::CCLabelTTF* label, float deltaX, float deltaY);
	static void moveTo(cocos2d::CCLabelTTF* label, float x, float y);
	static void moveToAbsolute(cocos2d::CCLabelTTF* label, float x, float y);

	static float getWidth(cocos2d::CCLabelTTF* label);
	static float getHeight(cocos2d::CCLabelTTF* label);
	static float getXMiddle(cocos2d::CCLabelTTF* label);

	enum position {RIGHT, LEFT, BOTTOM, TOP, MIDDLE};
	enum color {WHITE, BLACK, BLUE, GREEN, RED, GREY, BROWN, PINK, PURPLE, YELLOW, GOLD};
};

} /* namespace dxco */
#endif /* LABELUTIL_H_ */
