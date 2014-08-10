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
	this->speedDt = 0;

	//sprite sheet is created here but should be added as a map child outside
	this->enemySpriteSheet = cocos2d::CCSpriteBatchNode::create("sprite_sheets/zombies.png");
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
	this->speedDt += dt;
	if (this->speedDt > SPEED_DT){
		Enemy::ENEMY_SPEED = 1.1 * Enemy::ENEMY_SPEED;
		this->speedDt = 0;
	}
}

void EnemyFactory::createEnemy(GameModel* model) {

	//random sprite type
	std::string type;
	if (rand() % 2) {
		type = "campesino";
	} else {
		type = "oficinista";
	}

	std::map<int, dxco::Animation*> animations = loadAnimations(model, type, 0.02);
	cocos2d::CCSprite* enemySprite = createSpriteInRandomPosition(model, type + "_1_0000.png", 75, 75);

	Enemy* enemy = new Enemy(model, enemySprite, animations);
	addEnemy(model, enemy);

	SpriteUtil::fadeIn(enemy->getSprite());
}

void EnemyFactory::createBoss(GameModel* model) {

	std::map<int, dxco::Animation*> animations = loadAnimations(model, "elvis", 0.03);

	cocos2d::CCSprite* enemySprite = createSpriteInRandomPosition(model, "elvis_1_0000.png", 150, 150);
	Enemy* enemy = new Boss(model, enemySprite, animations);
	addEnemy(model, enemy);

	SpriteUtil::fadeIn(enemy->getSprite());
}

void EnemyFactory::addEnemy(GameModel* model, Enemy* enemy) {

	model->enemies.push_back(enemy);
	model->items.push_back(enemy);
	this->enemySpriteSheet->addChild(enemy->getSprite());
}

std::map<int, dxco::Animation*> EnemyFactory::loadAnimations(GameModel* model, std::string type, float frameTime) {

	std::map<int, dxco::Animation*> animations;

	for (int i = 0; i < ENEMY_ANGLE_POSITIONS; i++) {
		std::vector<cocos2d::CCSpriteFrame*> texturesStanding;
		texturesStanding.push_back(dxco::SpriteUtil::createSpriteFrame(type + "_" + dxco::StringUtil::toString(i + 1) + "_0000.png"));

		dxco::Animation* animation = new Animation(texturesStanding, frameTime);
		animations[Enemy::ENEMY_STANDING * ENEMY_ANGLE_POSITIONS + i] = animation;

		std::vector<cocos2d::CCSpriteFrame*> texturesWalking;

		for (int j = 0; j < 20; j++){
			std::string index = dxco::StringUtil::padLeft(j, 4);

			texturesWalking.push_back(dxco::SpriteUtil::createSpriteFrame(type + "_" + dxco::StringUtil::toString(i + 1) + "_" + index + ".png"));
		}

		animation = new Animation(texturesWalking, frameTime);
		animations[Enemy::ENEMY_WALKING * ENEMY_ANGLE_POSITIONS + i] = animation;
	}

	return animations;
}

cocos2d::CCSprite* EnemyFactory::createSpriteInRandomPosition(GameModel* model, std::string texture, int width, int height) {

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	//create sprite
	float x, y;
	bool selected = false;
	while (!selected) {
		x = width / 2 + rand() % int(model->mapa->getWidth() - width / 2);
		y = height / 2 + rand() % int(model->mapa->getHeight() - height / 2);

		float distance = MathUtil::distance(cocos2d::CCPoint(x, y), model->player->getLocation());
		selected = distance > model->player->getWidth() * 2;
	}
	return dxco::SpriteUtil::create(texture, x, y, width, height, true);
}

} /* namespace dxco */
