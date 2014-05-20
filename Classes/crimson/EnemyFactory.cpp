#include "EnemyFactory.h"
#include "../dxco/SpriteUtil.h"
#include "../dxco/StringUtil.h"
#include "../dxco/Animation.h"
#include "Enemy.h"
#include "Boss.h"
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
		this->bossDt = 0;
	}
}

void EnemyFactory::createEnemy(GameModel* model) {
	std::string snumber = StringUtil::toString(rand() % 8 + 1);

	//create sprite
	cocos2d::CCSprite* enemySprite = getRandomSprite(model, "citizenzombie" + snumber + ".png", 35, 35);

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
	model->mapa->addChild(enemy->getSprite());
}

/* create a sprite in a random position outside the map */
cocos2d::CCSprite* EnemyFactory::getRandomSprite(GameModel* model, std::string texture, int width, int height) {
	cocos2d::CCSize visibleSize =
				cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	bool upVisible = false;
	bool downVisible = false;
	bool leftVisible = false;
	bool rightVisible = false;

	if (model->mapa->getPositionX() > 0) {
		leftVisible = true;
	}
	if (model->mapa->getPositionX() + model->mapa->getWidth() < visibleSize.width) {
		rightVisible = true;
	}
	if (model->mapa->getPositionY() > 0) {
		downVisible = true;
	}
	if (model->mapa->getPositionY() + model->mapa->getHeight() < visibleSize.height) {
		upVisible = true;
	}


	float x, y;
	bool selected = false;
	while (!selected) {
		switch (rand() % 4) {
			case 0: { //top
				if (upVisible){
					continue;
				}
				x = rand() % int(visibleSize.width) - model->mapa->getPositionX();
				y = visibleSize.height - model->mapa->getPositionY() + height / 2;
				break;
			}
			case 1: { //bottom
				if (downVisible){
					continue;
				}
				x = rand() % int(visibleSize.width) - model->mapa->getPositionX();
				y = - model->mapa->getPositionY() - height / 2;
				break;
			}
			case 2: { //left
				if (leftVisible){
					continue;
				}
				x = - model->mapa->getPositionX() - width / 2;
				y = rand() % int(visibleSize.height) - model->mapa->getPositionY();
				break;
			}
			case 3: { //right
				if (rightVisible){
					continue;
				}
				x = visibleSize.width - model->mapa->getPositionX() + width / 2;
				y = rand() % int(visibleSize.height) - model->mapa->getPositionY();
				break;
			}
			}
		selected = true;
	}



	//create sprite
	return dxco::SpriteUtil::create(texture, x, y, width, height);
}

void EnemyFactory::createBoss(GameModel* model) {
	std::string snumber = StringUtil::toString(rand() % 8 + 1);

	//create sprite
	cocos2d::CCSprite* enemySprite = getRandomSprite(model, "citizenzombieboss.png", 120, 120);

	//new enemy
	std::map<int, dxco::Animation*> animations;
	std::vector<cocos2d::CCTexture2D*> textures;
	std::vector<cocos2d::CCTexture2D*> texturesMuerto;
	float frameTime = 0.18;

	dxco::Animation* animation = new Animation(textures, frameTime);

	texturesMuerto.push_back(dxco::SpriteUtil::createTexture("BloodSplat1.png"));
	animation = new Animation(texturesMuerto, 1);
	animations[Enemy::ENEMY_DEAD] = animation;

	Boss* enemy = new Boss(model, enemySprite, animations);

	model->enemies.push_back(enemy);
	model->items.push_back(enemy);
	model->vista->mapa->addChild(enemy->getSprite());
}

} /* namespace dxco */
