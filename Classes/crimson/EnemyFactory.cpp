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
	//create sprite
	cocos2d::CCSprite* enemySprite = getRandomSprite(model, "z1/1.png", 50, 50);

	float frameTime = 0.18;

	cocos2d::CCTexture2D* textureDead = dxco::SpriteUtil::createTexture("BloodSplat1.png");
	std::vector<cocos2d::CCTexture2D*> texturesDead;
	texturesDead.push_back(textureDead);
	dxco::Animation* deadAnimation = new Animation(texturesDead, frameTime);

	std::map<int, dxco::Animation*> animations;
	for (int i = 0; i < ENEMY_ANGLE_POSITIONS; i++) {
		std::vector<cocos2d::CCTexture2D*> texturesWalking;
		texturesWalking.push_back(dxco::SpriteUtil::createTexture("z1/" + dxco::StringUtil::toString(i + 1) + ".png"));
		dxco::Animation* animation = new Animation(texturesWalking, frameTime);
		animations[Enemy::ENEMY_WALKING * ENEMY_ANGLE_POSITIONS + i] = animation;

		std::vector<cocos2d::CCTexture2D*> texturesBeating;
		texturesBeating.push_back(dxco::SpriteUtil::createTexture("z1/" + dxco::StringUtil::toString(i + 1) + ".png"));
		texturesBeating.push_back(dxco::SpriteUtil::createTexture("z1/p" + dxco::StringUtil::toString(i + 1) + ".png"));
		animation = new Animation(texturesBeating, frameTime);
		animations[Enemy::ENEMY_BEATING * ENEMY_ANGLE_POSITIONS + i] = animation;

		animations[Enemy::ENEMY_DEAD * ENEMY_ANGLE_POSITIONS + i] = deadAnimation;
	}

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
		if(x < 0 || x > model->mapa->getWidth() || y < 0 || y > model->mapa->getHeight()){
			selected = false;
		}
	}



	//create sprite
	return dxco::SpriteUtil::create(texture, x, y, width, height);
}

void EnemyFactory::createBoss(GameModel* model) {

	//create sprite
	cocos2d::CCSprite* enemySprite = getRandomSprite(model, "b/1.png", 120, 120);
	float frameTime = 0.18;

	//new enemy
	cocos2d::CCTexture2D* textureDead = dxco::SpriteUtil::createTexture("BloodSplat1.png");
	std::vector<cocos2d::CCTexture2D*> texturesDead;
	texturesDead.push_back(textureDead);
	dxco::Animation* deadAnimation = new Animation(texturesDead, frameTime);

	std::map<int, dxco::Animation*> animations;
	for (int i = 0; i < ENEMY_ANGLE_POSITIONS; i++) {
		std::vector<cocos2d::CCTexture2D*> texturesWalking;
		texturesWalking.push_back(dxco::SpriteUtil::createTexture("b/" + dxco::StringUtil::toString(i + 1) + ".png"));
		dxco::Animation* animation = new Animation(texturesWalking, frameTime);
		animations[Enemy::ENEMY_WALKING * ENEMY_ANGLE_POSITIONS + i] = animation;

		animations[Enemy::ENEMY_DEAD * ENEMY_ANGLE_POSITIONS + i] = deadAnimation;
	}

	Enemy* enemy = new Boss(model, enemySprite, animations);

	model->enemies.push_back(enemy);
	model->items.push_back(enemy);
	model->mapa->addChild(enemy->getSprite());
}

} /* namespace dxco */
