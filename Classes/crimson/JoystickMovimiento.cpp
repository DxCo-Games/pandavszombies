#include "JoystickMovimiento.h"
#include "../dxco/SpriteUtil.h"
#include <math.h>

namespace dxco {

JoystickMovimiento::JoystickMovimiento(GameModel* game, cocos2d::CCSprite* sprite, float radio) : Joystick(sprite, radio) {
	this->game = game;
}

void JoystickMovimiento::onMoved(cocos2d::CCPoint location, float angle, float intensity) {
	Joystick::onMoved(location, angle, intensity);
	this->game->player->move(cos(angle) * PLAYER_SPEED, sin(angle) * PLAYER_SPEED);
}

} /* namespace dxco */
