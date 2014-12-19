#include "JoystickMira.h"
#include "../dxco/SpriteUtil.h"
#include "../HelloWorldScene.h"

namespace dxco {

JoystickMira::JoystickMira(GameModel* game, cocos2d::CCSprite* sprite,
		float radio) :
		Joystick(sprite, radio) {
	this->game = game;
}

void JoystickMira::onMoved(cocos2d::CCPoint location, float angle,
		float intensity) {
	Joystick::onMoved(location, angle, intensity);

	float rotation = -angle * 57.2957795;
	float moveAngle = this->game->player->moveRotation * -57.2957795;
	bool invertido;

	if ((-rotation < 90 && -moveAngle > 270) || (-moveAngle < 90 && -rotation > 270)) {
		invertido = false;
	} else {
		int diff = abs(rotation - moveAngle);
		invertido = diff > 120;
	}

	this->game->player->invertido = invertido;
	this->game->player->rotation = rotation;
	this->game->player->rotating = true;
	this->game->vista->fire->setAngle(angle * 57.2957795);
}

void JoystickMira::onTouchedEnded(cocos2d::CCPoint location, float angle, float intensity) {
	Joystick::onTouchedEnded(location, angle, intensity);
	this->game->player->rotating = false;
}

} /* namespace dxco */
