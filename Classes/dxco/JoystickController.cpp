#include "JoystickController.h"
#include <math.h>

#include "MathUtil.h"

namespace dxco {

void JoystickController::addJoystick(Joystick* joystick) {
	angulo = 0;
	this->joysticks.push_back(joystick);
}

void JoystickController::ccTouchesBegan(cocos2d::CCSet *pTouches,
		cocos2d::CCEvent *pEvent) {
	cocos2d::CCSetIterator it = pTouches->begin();
	cocos2d::CCPoint location;
	cocos2d::CCTouch * touch;

	for (int iTouchCount = 0; iTouchCount < pTouches->count(); iTouchCount++) {
		touch = (cocos2d::CCTouch*) (*it);
		location = touch->getLocationInView();
		location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

		this->beginLocations[touch->getID()] = location;

		Joystick* joystick = getRelatedJoystick(location);

		if (joystick) {
			cocos2d::CCPoint center = joystick->getCenter();
			float intensity = MathUtil::distance(location, joystick->getCenter());

			joystick->onTouchedBegan(location, 0, intensity);
		}

		it++;
	}

}

void JoystickController::ccTouchesEnded(cocos2d::CCSet *pTouches,
		cocos2d::CCEvent *pEvent) {

	cocos2d::CCSetIterator it = pTouches->begin();
	cocos2d::CCPoint location;
	cocos2d::CCTouch * touch;

	for (int iTouchCount = 0; iTouchCount < pTouches->count(); iTouchCount++) {
		touch = (cocos2d::CCTouch*) (*it);
		location = touch->getLocationInView();
		location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

		this->beginLocations[touch->getID()] = location;

		Joystick* joystick = getRelatedJoystick(location);
		if (joystick) {
			cocos2d::CCPoint center = joystick->getCenter();
			float intensity = MathUtil::distance(location, joystick->getCenter());

			joystick->onTouchedEnded(location, 0, intensity);
		}

		it++;
	}
}


void JoystickController::ccTouchesMoved(cocos2d::CCSet *pTouches,
		cocos2d::CCEvent *pEvent) {

	cocos2d::CCSetIterator it = pTouches->begin();
	cocos2d::CCPoint location;
	cocos2d::CCTouch * touch;

	for (int iTouchCount = 0; iTouchCount < pTouches->count(); iTouchCount++) {

		touch = (cocos2d::CCTouch*) (*it);
		location = touch->getLocationInView();
		location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

		this->beginLocations[touch->getID()] = location;

		Joystick* joystick = getRelatedJoystick(location);

		if (joystick) {
			cocos2d::CCPoint center = joystick->getCenter();
			float intensity = MathUtil::distance(location, joystick->getCenter());

			joystick->onMoved(location, MathUtil::angle(joystick->getCenter(), location),
					intensity);
		}

		it++;
	}
}

Joystick* JoystickController::getRelatedJoystick(cocos2d::CCPoint location) {
	Joystick* result = NULL;

	if (joysticks.size()) {
		result = joysticks[0];
		float minDistance = MathUtil::distance(location, result->getCenter());

		for (int i = 1; i < this->joysticks.size(); i++) {
			Joystick* joystick = this->joysticks[i];
			float currDistance = MathUtil::distance(location, joystick->getCenter());

			if (currDistance < minDistance) {
				result = joystick;
			}
		}

	}

	return result;
}

} /* namespace dxco */
