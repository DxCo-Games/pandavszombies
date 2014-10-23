#include "Boss.h"
#include "../../HelloWorldScene.h"
#include "../../dxco/VoiceManager.h"

namespace dxco {

Boss::Boss(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int level) :
	Enemy(model, sprite, animations, level),
	Item(sprite, animations) {
	this->life = 50 * (level +1);
	this->score = 50 * (level +1);
	this->strength = 25 * (level +1);
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
