#ifndef TOUCHABLE_H_
#define TOUCHABLE_H_
#define LOG_TOUCH_POSITION 0

#include "cocos2d.h"

namespace dxco {

class Touchable {
public:
	Touchable(cocos2d::CCNode* sprite);
	virtual ~Touchable();
	void touch(cocos2d::CCPoint location);

	void on();
	void off();

	virtual void execute() = 0;

	cocos2d::CCNode* getSprite();
protected:
	bool isTouched(cocos2d::CCPoint location);
	cocos2d::CCNode* sprite;
};

} /* namespace dxco */
#endif /* TOUCHABLE_H_ */
