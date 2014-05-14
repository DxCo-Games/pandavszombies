#include "GameFactory.h"
#include "../dxco/SpriteUtil.h"
#include "../dxco/Animation.h"
#include "Enemy.h"

namespace dxco {

Enemy* GameFactory::createEnemy(GameModel* model) {
	//make random point
	cocos2d::CCSize visibleSize =
			cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	float x, y;
	switch (rand() % 4) {
	case 0: { //top
		x = rand() % int(visibleSize.width);
		y = visibleSize.height + 30;
		break;
	}
	case 1: { //bottom
		x = rand() % int(visibleSize.width);
		y = -30;
		break;
	}
	case 2: { //left
		x = -30;
		y = rand() % int(visibleSize.height);
		break;
	}
	case 3: { //right
		x = visibleSize.width + 30;
		y = rand() % int(visibleSize.height);
		break;
	}
	}

	//create sprite
	cocos2d::CCSprite* enemySprite = dxco::SpriteUtil::create(
			"citizenzombie1.png", x, y, 35, 35);

	//new enemy
	std::map<int, dxco::Animation*> animations;
	std::vector<cocos2d::CCTexture2D*> textures;
	std::vector<cocos2d::CCTexture2D*> texturesMuerto;
	float frameTime = 0.18;


	textures.push_back(dxco::SpriteUtil::createTexture("citizenzombie1.png"));
	textures.push_back(dxco::SpriteUtil::createTexture("citizenzombie1-pega.png"));

	dxco::Animation* animation = new Animation(textures, frameTime);

	animations[Enemy::ENEMY_BEATING] = animation;

	texturesMuerto.push_back(dxco::SpriteUtil::createTexture("BloodSplat1.png"));
	animation = new Animation(texturesMuerto, 1);

	animations[Enemy::ENEMY_DEAD] = animation;
	return new Enemy(model, enemySprite, animations);
}

} /* namespace dxco */
