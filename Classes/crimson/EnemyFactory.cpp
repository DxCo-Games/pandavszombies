#include "EnemyFactory.h"
#include "../dxco/SpriteUtil.h"
#include "../dxco/StringUtil.h"
#include "../dxco/Animation.h"
#include "../dxco/MathUtil.h"
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
	//random sprite type
	std::string type;
	if (rand() % 2) {
		type = "campesino_";
	} else {
		type = "oficinista_";
	}

	//create sprite
	cocos2d::CCSprite* enemySprite = getRandomSprite(model, "zombies/" + type + "1_0000.png", 75, 75);
	float frameTime = 0.02;

	std::map<int, dxco::Animation*> animations;
	for (int i = 0; i < ENEMY_ANGLE_POSITIONS; i++) {
		std::vector<cocos2d::CCTexture2D*> texturesStanding;
		texturesStanding.push_back(dxco::SpriteUtil::createTexture("zombies/" + type + dxco::StringUtil::toString(i + 1) + "_0000.png"));
		dxco::Animation* animation = new Animation(texturesStanding, frameTime);
		animations[Enemy::ENEMY_STANDING * ENEMY_ANGLE_POSITIONS + i] = animation;

		std::vector<cocos2d::CCTexture2D*> texturesWalking;
		for (int j = 0; j < 20; j++){
			std::string index = "00" + dxco::StringUtil::toString(j);
			if (j < 10){
				index = "0" + index;
			}

			texturesWalking.push_back(dxco::SpriteUtil::createTexture("zombies/" + type + dxco::StringUtil::toString(i + 1)
			+ "_" + index + ".png"));
		}
		animation = new Animation(texturesWalking, frameTime);
		animations[Enemy::ENEMY_WALKING * ENEMY_ANGLE_POSITIONS + i] = animation;
	}

	Enemy* enemy = new Enemy(model, enemySprite, animations);

	model->enemies.push_back(enemy);
	model->items.push_back(enemy);
	model->mapa->addChild(enemy->getSprite());

	enemy->getSprite()->setOpacity(0);
	cocos2d::CCAction *action = cocos2d::CCFadeIn::create(1);
	enemy->getSprite()->runAction(action);
}

/* create a sprite in a random position outside the map */
cocos2d::CCSprite* EnemyFactory::getRandomSprite(GameModel* model, std::string texture, int width, int height) {

	cocos2d::CCSize visibleSize =
				cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	//create sprite
	float x, y;
	bool selected = false;
	while (!selected) {
		x = rand() % int(model->mapa->getWidth());
		y = rand() % int(model->mapa->getHeight());

		float distance = MathUtil::distance(cocos2d::CCPoint(x, y), model->player->getLocation());
		selected = distance > model->player->getWidth() * 2;
	}
	return dxco::SpriteUtil::create(texture, x, y, width, height);
}

//TODO too much duplication
void EnemyFactory::createBoss(GameModel* model) {

	//create sprite
	cocos2d::CCSprite* enemySprite = getRandomSprite(model, "zombies/elvis_1_0000.png", 110, 110);
	float frameTime = 0.03;

	std::map<int, dxco::Animation*> animations;
	for (int i = 0; i < ENEMY_ANGLE_POSITIONS; i++) {
		std::vector<cocos2d::CCTexture2D*> texturesStanding;
		texturesStanding.push_back(dxco::SpriteUtil::createTexture("zombies/elvis_" + dxco::StringUtil::toString(i + 1) + "_0000.png"));
		dxco::Animation* animation = new Animation(texturesStanding, frameTime);
		animations[Enemy::ENEMY_STANDING * ENEMY_ANGLE_POSITIONS + i] = animation;

		std::vector<cocos2d::CCTexture2D*> texturesWalking;
		for (int j = 0; j < 20; j++){
			std::string index = "00" + dxco::StringUtil::toString(j);
			if (j < 10){
				index = "0" + index;
			}

			texturesWalking.push_back(dxco::SpriteUtil::createTexture("zombies/elvis_" + dxco::StringUtil::toString(i + 1)
			+ "_" + index + ".png"));
		}
		animation = new Animation(texturesWalking, frameTime);
		animations[Enemy::ENEMY_WALKING * ENEMY_ANGLE_POSITIONS + i] = animation;
	}

	Enemy* enemy = new Boss(model, enemySprite, animations);

	model->enemies.push_back(enemy);
	model->items.push_back(enemy);
	model->mapa->addChild(enemy->getSprite());

	enemy->getSprite()->setOpacity(0);
	cocos2d::CCAction *action = cocos2d::CCFadeIn::create(1);
	enemy->getSprite()->runAction(action);
}

} /* namespace dxco */
