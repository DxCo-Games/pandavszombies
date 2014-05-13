#include "JoystickMovimiento.h"
#include "../dxco/SpriteUtil.h"
#include <math.h>
namespace dxco {

JoystickMovimiento::JoystickMovimiento(GameModel* game, cocos2d::CCSprite* sprite, float radio) : Joystick(sprite, radio) {
	this->game = game;
}

void JoystickMovimiento::onMoved(cocos2d::CCPoint location, float angle, float intensity) {
	Joystick::onMoved(location, angle, intensity);

	float x = this->game->player->getLocation().x;
	float y = this->game->player->getLocation().y;
	float deltaX = cos(angle) * intensity / 15;
	float deltaY = sin(angle) * intensity / 15;
	cocos2d::CCSize size = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	if (x + deltaX > 0 && x + deltaX < size.width && y + deltaY > 0 && y + deltaY < size.height){
		this->game->player->move(deltaX, deltaY);
	}
}

} /* namespace dxco */
