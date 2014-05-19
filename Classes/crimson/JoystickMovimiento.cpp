#include "JoystickMovimiento.h"
#include "../dxco/SpriteUtil.h"
#include <math.h>

namespace dxco {

JoystickMovimiento::JoystickMovimiento(GameModel* game, cocos2d::CCSprite* sprite, float radio) : Joystick(sprite, radio) {
	this->game = game;
}

void JoystickMovimiento::onMoved(cocos2d::CCPoint location, float angle, float intensity) {
	Joystick::onMoved(location, angle, intensity);
	this->game->player->angle = angle;
	this->game->player->moving = true;
}


void JoystickMovimiento::onTouchedEnded(cocos2d::CCPoint location, float angle, float intensity) {
	Joystick::onTouchedEnded(location, angle, intensity);
	this->game->player->moving = false;
}

} /* namespace dxco */
