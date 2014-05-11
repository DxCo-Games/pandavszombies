#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "cocos2d.h"
namespace dxco {

class Joystick {

public:
	Joystick(cocos2d::CCSprite* sprite, float radio);
	virtual void onTouchedBegan(cocos2d::CCPoint location, float angle, float intensity);
	virtual void onMoved(cocos2d::CCPoint location, float angle, float intensity);
	virtual void onTouchedEnded(cocos2d::CCPoint location, float angle, float intensity);
	cocos2d::CCPoint getCenter();
	float getRadio();
private:
	cocos2d::CCSprite* sprite;
	cocos2d::CCPoint center;
	float radio;
};

} /* namespace dxco */
#endif /* JOYSTICK_H_ */
