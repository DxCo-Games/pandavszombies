#include "JoystickController.h"
#include <math.h>
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
			float intensity = this->distance(location, joystick->getCenter());

			joystick->onTouchedBegan(location, 0, intensity);
		}

		it++;
	}

}

float JoystickController::distance(cocos2d::CCPoint a, cocos2d::CCPoint b) {
	float x = a.x - b.x;
	float y = a.y - b.y;
	x = x * x;
	y = y * y;

	return sqrt(x + y);
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
			float intensity = this->distance(location, joystick->getCenter());

			joystick->onTouchedEnded(location, 0, intensity);
		}

		it++;
	}
}

float JoystickController::angle(cocos2d::CCPoint center,
		cocos2d::CCPoint pointA) {

	float result = 0;

	if (pointA.y > center.y) {
		// cuadrante 1
		if (pointA.x > center.x) {
			double adyacente = pointA.x - center.x;
			double hipotenusa = distance(pointA, center);

			result = acos(adyacente / hipotenusa);
		} else { // cuadrante 2
			double adyacente = pointA.y - center.y;
			double hipotenusa = distance(pointA, center);

			result = acos(adyacente / hipotenusa) + (PI * 0.5);
		}
	} else {
		// cuadrante 3
		if (pointA.x < center.x) {
			double adyacente = center.x - pointA.x;
			double hipotenusa = distance(pointA, center);

			result = acos(adyacente / hipotenusa) + PI;
		} else { // cuadrante 4
			double adyacente = center.y - pointA.y;
			double hipotenusa = distance(pointA, center);

			result = acos(adyacente / hipotenusa) + (PI * 1.5);
		}
	}

	return result;
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
			float intensity = this->distance(location, joystick->getCenter());

			joystick->onMoved(location, angle(joystick->getCenter(), location),
					intensity);
		}

		it++;
	}
}

Joystick* JoystickController::getRelatedJoystick(cocos2d::CCPoint location) {
	Joystick* result = NULL;

	if (joysticks.size()) {
		result = joysticks[0];
		float minDistance = distance(location, result->getCenter());

		for (int i = 1; i < this->joysticks.size(); i++) {
			Joystick* joystick = this->joysticks[i];
			float currDistance = distance(location, joystick->getCenter());

			if (currDistance < minDistance) {
				result = joystick;
			}
		}

	}

	return result;
}

} /* namespace dxco */
