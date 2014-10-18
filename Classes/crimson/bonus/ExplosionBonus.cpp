#include "ExplosionBonus.h"
#include "../GameModel.h"
#include "../Enemy.h"
#include "../../dxco/SpriteUtil.h"
#include "../../HelloWorldScene.h"
#include "../../dxco/MathUtil.h"

namespace dxco {

ExplosionBonus::ExplosionBonus(GameModel* model, cocos2d::CCSprite* sprite,
		std::map<int, Animation*>& animations): Bonus(model, sprite, animations) {
}

void ExplosionBonus::applyBonus(){
	cocos2d::CCParticleSystemQuad* firework = cocos2d::CCParticleSystemQuad::create("ball.plist");

	firework->setPosition(this->getLocation());
	firework->setPositionType(cocos2d::kCCPositionTypeRelative);
	this->model->vista->clouds->addChild(firework);

	for (int i = 0; i < this->model->enemies.size(); i++) {
		Enemy* enemy = this->model->enemies[i];

		if (MathUtil::distance(firework->getPosition(), enemy->getLocation()) < EXPLOSION_RANGE) {
			enemy->hurt(EXPLOSION_DAMAGE);
		}
	}
}

} /* namespace dxco */
