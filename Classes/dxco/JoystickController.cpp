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

		this->setRelatedJoystick(touch->getID(), location);
		Joystick* joystick = this->getRelatedJoystick(touch->getID());

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

		Joystick* joystick = getRelatedJoystick(touch->getID());

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

		Joystick* joystick = getRelatedJoystick(touch->getID());

		if (joystick) {
			cocos2d::CCPoint center = joystick->getCenter();
			float intensity = MathUtil::distance(location, joystick->getCenter());

			joystick->onMoved(location, MathUtil::angle(joystick->getCenter(), location),
					intensity);
		}

		it++;
	}
}


void JoystickController::setRelatedJoystick(int id, cocos2d::CCPoint location) {
	Joystick* joystick = NULL;

	for (int i = 0; i < this->joysticks.size(); i++) {
		float distance = MathUtil::distance(this->joysticks[i]->getCenter(), location);

		if (distance <= this->joysticks[i]->getRadio()) {
			joystick = this->joysticks[i];
		}
	}

	this->relatedJoysticks[id] = joystick;
}

Joystick* JoystickController::getRelatedJoystick(int id) {
	return this->relatedJoysticks[id];
}
} /* namespace dxco */
