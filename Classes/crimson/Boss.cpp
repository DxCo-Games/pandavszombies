#include "Boss.h"
#include "../HelloWorldScene.h"
#include "../dxco/VoiceManager.h"

namespace dxco {

Boss::Boss(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, float speed) :
	Enemy(model, sprite, animations, speed),
	Item(sprite, animations) {
	this->life = 120;
	this->score = 50;
	this->strength = 50;
	this->mass = 0.75 * ENEMY_DEFAULT_SPEED / speed;
}

float Boss::getColitionRatio() {
	return 0.2 * this->getWidth();
}

void Boss::kill() {
	Enemy::kill();
	this->model->voice->play("voices/rock.ogg", "voices/cake.ogg");
}


} /* namespace dxco */
