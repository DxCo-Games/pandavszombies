#ifndef JOYSTICKMOVIMIENTO_H_
#define JOYSTICKMOVIMIENTO_H_

#include "../dxco/Joystick.h"
#include "GameModel.h"

namespace dxco {

class JoystickMovimiento : public Joystick {

public:
	JoystickMovimiento(GameModel* game, cocos2d::CCSprite* sprite, float radio);
	void onMoved(cocos2d::CCPoint location, float angle, float intensity);
	void onTouchedEnded(cocos2d::CCPoint location, float angle, float intensity);
	GameModel* game;
	float width;
	float height;
};

} /* namespace dxco */
#endif /* JOYSTICKMOVIMIENTO_H_ */
