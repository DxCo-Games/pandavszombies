#include "EnemyFactory.h"
#include "../dxco/SpriteUtil.h"
#include "../dxco/StringUtil.h"
#include "../dxco/Animation.h"
#include "Enemy.h"
#include "GameModel.h"
#include "HelloWorldScene.h"

namespace dxco {

EnemyFactory::EnemyFactory(){
	this->enemyDt = 0;
	this->bossDt = 0;
}

void EnemyFactory::update(GameModel* model, float dt) {
	this->enemyDt += dt;
	if (this->enemyDt > ENEMY_DT){
		this->createEnemy(model);
		this->enemyDt = 0;
	}

	this->bossDt += dt;
	if (this->bossDt > BOSS_DT){
		this->createBoss(model);
		this->enemyDt = 0;
	}
}

void EnemyFactory::createEnemy(GameModel* model) {
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

	std::string snumber = StringUtil::toString(rand() % 8 + 1);

	//create sprite
	cocos2d::CCSprite* enemySprite = dxco::SpriteUtil::create(
			"citizenzombie" + snumber + ".png", x, y, 35, 35);

	//new enemy
	std::map<int, dxco::Animation*> animations;
	std::vector<cocos2d::CCTexture2D*> textures;
	std::vector<cocos2d::CCTexture2D*> texturesMuerto;
	float frameTime = 0.18;

	//FIXME animate the rest of the zombies
	if (snumber == "1") {
		textures.push_back(dxco::SpriteUtil::createTexture("citizenzombie1.png"));
		textures.push_back(dxco::SpriteUtil::createTexture("citizenzombie1-pega.png"));
	} else {
		textures.push_back(dxco::SpriteUtil::createTexture("citizenzombie" + snumber + ".png"));
		textures.push_back(dxco::SpriteUtil::createTexture("citizenzombie" + snumber + ".png"));
	}

	dxco::Animation* animation = new Animation(textures, frameTime);

	animations[Enemy::ENEMY_BEATING] = animation;

	texturesMuerto.push_back(dxco::SpriteUtil::createTexture("BloodSplat1.png"));
	animation = new Animation(texturesMuerto, 1);

	animations[Enemy::ENEMY_DEAD] = animation;
	Enemy* enemy = new Enemy(model, enemySprite, animations);

	model->enemies.push_back(enemy);
	model->items.push_back(enemy);
	model->vista->addChild(enemy->getSprite());
}

void EnemyFactory::createBoss(GameModel* model) {

}

} /* namespace dxco */
