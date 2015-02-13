#include "Boss.h"
#include "../../HelloWorldScene.h"
#include "../../dxco/VoiceManager.h"

namespace dxco {

Boss::Boss(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int level, std::string type) :
	Enemy(model, sprite, animations, level, type),
	Item(sprite, animations) {
	this->life = 5 * this->life;
	this->score = 5 * this->score;
	this->strength = 5 * this->strength;
	this->mass = 0.75 * Enemy::getSpeed(1) / speed;
}

float Boss::getColitionRatio() {
	return 0.2 * this->getWidth();
}

void Boss::kill() {
	this->model->voice->play("voices/rock.ogg", "voices/cake.ogg");
	Enemy::kill();
}


} /* namespace dxco */
