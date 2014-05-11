#ifndef JOYSTICKMIRA_H_
#define JOYSTICKMIRA_H_

#include "../dxco/Joystick.h"
#include "GameModel.h"

namespace dxco {

class JoystickMira : public Joystick {
public:
	JoystickMira(GameModel* game, cocos2d::CCSprite* sprite, float radio);
	void onMoved(cocos2d::CCPoint location, float angle, float intensity);
	GameModel* game;
};

} /* namespace dxco */
#endif /* JOYSTICKMIRA_H_ */
