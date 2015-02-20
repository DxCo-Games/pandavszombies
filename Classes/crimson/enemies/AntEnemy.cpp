#include "AntEnemy.h"

namespace dxco {

AntEnemy::AntEnemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int level, std::string type): Enemy(model, sprite, animations, level, type), Item(sprite, animations) {
	this->score = this->score / 50;
	this->life = this->life / 50;
	this->strength = this->strength / 50;
}

float AntEnemy::getWidth() {
	// para mejorar colisiones
	return Item::getWidth() * 3;
}

} /* namespace dxco */
