#ifndef JOYSTICKCONTROLLER_H_
#define JOYSTICKCONTROLLER_H_

#include "Joystick.h"
#include <vector>

#define PI 3.14159265359

namespace dxco {

class JoystickController {
public:
	void addJoystick(Joystick* joystick);

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
private:
	std::vector<Joystick*> joysticks;
	std::map<int, cocos2d::CCPoint> beginLocations;
	Joystick* getRelatedJoystick(cocos2d::CCPoint location);
	float angulo;
};

} /* namespace dxco */
#endif /* JOYSTICKCONTROLLER_H_ */
