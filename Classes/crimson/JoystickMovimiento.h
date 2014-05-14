#ifndef JOYSTICKMOVIMIENTO_H_
#define JOYSTICKMOVIMIENTO_H_

#define PLAYER_SPEED 1.5

#include "../dxco/Joystick.h"
#include "GameModel.h"

namespace dxco {

class JoystickMovimiento : public Joystick {

public:
	JoystickMovimiento(GameModel* game, cocos2d::CCSprite* sprite, float radio);
	void onMoved(cocos2d::CCPoint location, float angle, float intensity);
	GameModel* game;
};

} /* namespace dxco */
#endif /* JOYSTICKMOVIMIENTO_H_ */
