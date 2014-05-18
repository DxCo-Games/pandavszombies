#include "JoystickMovimiento.h"
#include "../dxco/SpriteUtil.h"
#include <math.h>

namespace dxco {

JoystickMovimiento::JoystickMovimiento(GameModel* game, cocos2d::CCSprite* sprite, float radio) : Joystick(sprite, radio) {
	this->game = game;
	cocos2d::CCSize size = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	this->width = size.width * 2;
	this->height = size.height * 2;
}

void JoystickMovimiento::onMoved(cocos2d::CCPoint location, float angle, float intensity) {
	Joystick::onMoved(location, angle, intensity);

	cocos2d::CCPoint position = this->game->player->getLocation();

	float x = position.x;
	float y = position.y;

	float deltaX = cos(angle) * PLAYER_SPEED;
	float deltaY = sin(angle) * PLAYER_SPEED;

	float finalX = x + deltaX;
	float finalY = y + deltaY;

	if (finalX > 0 && finalX < this->width && finalY > 0 && finalY < this->height){
		this->game->mapa->move(-deltaX, -deltaY);
	}
}

} /* namespace dxco */
