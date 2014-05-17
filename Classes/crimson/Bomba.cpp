#include "Bomba.h"
#include "GameModel.h"
#include "../dxco/SpriteUtil.h"
#include "../HelloWorldScene.h"
#include "Enemy.h"
#include "../dxco/MathUtil.h"

namespace dxco {

Bomba::Bomba(GameModel* model) {
	this->model = model;
}

void Bomba::explode(float radio) {
	cocos2d::CCTexture2D* texture = dxco::SpriteUtil::createTexture("star.png");
	cocos2d::CCParticleExplosion* firework = cocos2d::CCParticleExplosion::create();
	//cocos2d::CCParticleGalaxy * firework = cocos2d::CCParticleGalaxy::create();;
	cocos2d::CCSize visibleSize =
				cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	float x = rand() % int(visibleSize.width);
	float y = rand() % int(visibleSize.height);

	firework->setPosition(x, y);
	firework->setTexture(texture);
	firework->setEndSize(radio);
	firework->setLife(0.5);

	this->model->mapa->addChild(firework);

	for (int i = 0; i < this->model->enemies.size(); i++) {
		Enemy* enemy = this->model->enemies[i];

		if (MathUtil::distance(firework->getPosition(), enemy->getLocation()) < visibleSize.width * 0.2) {
			enemy->hurt(50);
		}
	}
}

} /* namespace dxco */
