#include "BombEnemy.h"
#include "../GameModel.h"
#include "cocos2d.h"
#include "../../dxco/MathUtil.h"
#include "../../HelloWorldScene.h"
#include "../GameProperties.h"

namespace dxco {

BombEnemy::BombEnemy(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int level, std::string type): Enemy(model, sprite, animations, level, type), Item(sprite, animations) {

}

void BombEnemy::kill() {
	Enemy::kill();

	cocos2d::CCParticleSystemQuad* firework = cocos2d::CCParticleSystemQuad::create("bazooka_ball.plist");

	firework->setPosition(this->getLocation());
	firework->setPositionType(cocos2d::kCCPositionTypeRelative);
	this->model->vista->clouds->addChild(firework);
	this->model->vista->playEffect("sounds/bazooka.ogg");

	for (int i = 0; i < this->model->enemies.size(); i++) {
		Enemy* enemy = this->model->enemies[i];

		if (MathUtil::distance(firework->getPosition(), enemy->getLocation()) < ENEMY_EXPLOSION_RANGE) {
			enemy->hurt(this->model->prop->get("attack.damage")* 5);
		}
	}

	// tambien ataco al panda =(
	if (MathUtil::distance(firework->getPosition(), this->model->player->getLocation()) < ENEMY_EXPLOSION_RANGE) {
		this->beat(this->model->player, 0.2);
	}
}

} /* namespace dxco */
