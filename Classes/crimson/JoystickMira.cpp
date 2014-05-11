#include "JoystickMira.h"
#include "../dxco/SpriteUtil.h"
namespace dxco {

JoystickMira::JoystickMira(GameModel* game, cocos2d::CCSprite* sprite, float radio) : Joystick(sprite, radio) {
	this->game = game;
}

void JoystickMira::onMoved(cocos2d::CCPoint location, float angle, float intensity) {
	Joystick::onMoved(location, angle, intensity);

	SpriteUtil::rotateToDegree(this->game->player->getSprite(), - angle * 57.2957795);
}

} /* namespace dxco */
