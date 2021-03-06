#include "BazookaBullet.h"
#include "GameModel.h"
#include "GameProperties.h"
#include "cocos2d.h"
#include "../dxco/MathUtil.h"
#include "HelloWorldScene.h"

namespace dxco {

BazookaBullet::BazookaBullet(GameModel* model, cocos2d::CCSprite* sprite, float angle, std::map<int, Animation*>& animations) : Bullet(sprite, angle, animations) {
	this->model = model;
}

void BazookaBullet::update(float dt) {
	if (!this->used) {
		Item::update(dt);
		this->move(cos(this->angle) * BULLET_SPEED * dt, sin(this->angle) * BULLET_SPEED * dt);
	}
}

void BazookaBullet::use() {
	cocos2d::CCParticleSystemQuad* firework = cocos2d::CCParticleSystemQuad::create("bazooka_ball.plist");

	firework->setPosition(this->getLocation());
	firework->setPositionType(cocos2d::kCCPositionTypeRelative);

	this->model->vista->clouds->addChild(firework);
	this->model->vista->playEffect("sounds/bazooka.ogg");

	for (int i = 0; i < this->model->enemies.size(); i++) {
		Enemy* enemy = this->model->enemies[i];

		if (MathUtil::distance(firework->getPosition(), enemy->getLocation())
				< BAZOOKA_RANGE) {
			enemy->hurt(this->model->prop->get("attack.damage") * 5);
		}
	}

	this->used = true;
	this->getSprite()->removeFromParent();
}


} /* namespace dxco */
