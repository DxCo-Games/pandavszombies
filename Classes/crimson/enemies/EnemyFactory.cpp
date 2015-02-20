#include "EnemyFactory.h"
#include "../../dxco/SpriteUtil.h"
#include "../../dxco/StringUtil.h"
#include "../../dxco/Animation.h"
#include "../../dxco/MathUtil.h"
#include "BombEnemy.h"
#include "Enemy.h"
#include "Boss.h"
#include "SuperBoss.h"
#include "../GameModel.h"
#include "../levels/Level.h"
#include "../GameProperties.h"
#include "../../HelloWorldScene.h"
#include <algorithm>

namespace dxco {


EnemyFactory::EnemyFactory(){
}

void EnemyFactory::createEnemy(GameModel* model, std::vector<std::string>types, std::string type, float freq) {
	std::vector<std::string> vec;
	//20 is equally probable, 15 is less, 5 is lesser...
	if (rand() % 100 < freq * 100) {
		//if probabilty take the kill count one
		vec.push_back(type);
	} else {
		if (types.size()) {
			//if a types set is specified use it
			vec = types;
		} else {
			//if no types, use all except the kill count one
			vec.push_back("campesino");
			vec.push_back("oficinista");
			vec.push_back("basquet");
			vec.push_back("cirujano");
			vec.push_back("cura");
			//remove kill count type
			vec.erase(std::remove(vec.begin(), vec.end(), type), vec.end());
		}
	}
	this->createEnemy(model, vec);
}

void EnemyFactory::createEnemy(GameModel* model, std::vector<std::string>types) {
	if (model->enemies.size() > MAX_CONCURRENT_ZOMBIES) {
		model->level->totalEnemies -= 1;
		return;
	}
	Enemy *enemy = this->getEnemy(model, types);
	addEnemy(model, enemy);

	SpriteUtil::fadeIn(enemy->getSprite());
}

Enemy* EnemyFactory::getEnemy(GameModel* model, std::vector<std::string>types) {
	//random sprite type
	std::string type = types[rand() % types.size()];

	int delta = (rand() % 10);
	int enemyLevel = model->prop->get("enemy.level");
	float speed = Enemy::getSpeed(enemyLevel);
	if (type == "basquet") {
		delta += 10;
		speed = speed * 1.8;
	}

	std::map<int, dxco::Animation*> animations = loadAnimations(model, type, speed);
	cocos2d::CCSprite* enemySprite = createSpriteInRandomPosition(model, type + "_1_0000.png", 15 + delta, 15 + delta);

	Enemy* enemy = new Enemy(model, enemySprite, animations, enemyLevel, type);
	//FIXME add SpeedyEnemy
	if (type == "basquet") {
		enemy->speed = speed;
	}

	return enemy;
}

void EnemyFactory::createPanda(GameModel* model) {
	if (model->enemies.size() > MAX_CONCURRENT_ZOMBIES) {
		model->level->totalEnemies -= 1;
		return;
	}
	int enemyLevel = model->prop->get("enemy.level");

	std::map<int, dxco::Animation*> animations = pandaAnimations(model);
	cocos2d::CCSprite* enemySprite = createSpriteInRandomPosition(model, "herida1_5_0000.png", 75, 75);
	Enemy* enemy = new Enemy(model, enemySprite, animations, enemyLevel, "cura");
	enemySprite->setColor(cocos2d::ccc3(60, 100, 60));
	enemy->baseColor = cocos2d::ccc3(60, 100, 60);
	enemy->anglePositions = 16;
	addEnemy(model, enemy);
	SpriteUtil::fadeIn(enemy->getSprite());
}

void EnemyFactory::createPandaBoss(GameModel* model) {
	if (model->enemies.size() > MAX_CONCURRENT_ZOMBIES) {
		model->level->totalEnemies -= 1;
		return;
	}
	int enemyLevel = model->prop->get("enemy.level");

	std::map<int, dxco::Animation*> animations = pandaAnimations(model);
	cocos2d::CCSprite* enemySprite = createSpriteInRandomPosition(model, "herida1_5_0000.png", 150, 150);
	Boss* enemy = new Boss(model, enemySprite, animations, enemyLevel, "cura");
	enemySprite->setColor(cocos2d::ccc3(60, 100, 60));
	enemy->baseColor = cocos2d::ccc3(60, 100, 60);
	enemy->anglePositions = 16;
	addEnemy(model, enemy);
	SpriteUtil::fadeIn(enemy->getSprite());
}

void EnemyFactory::createBoss(GameModel* model) {
	this->createBoss(model, this->createTypesVector(true));
}

void EnemyFactory::createBombEnemy(GameModel* model) {
	this->createBombEnemy(model, this->createTypesVector(true));
}

void EnemyFactory::createBombEnemy(GameModel* model, std::vector<std::string>types) {

	if (model->enemies.size() > MAX_CONCURRENT_ZOMBIES) {
		model->level->totalEnemies -= 1;
		return;
	}

	std::string type = types[rand() % types.size()];

	int delta = (rand() % 10);
	int enemyLevel = model->prop->get("enemy.level");
	float speed = Enemy::getSpeed(enemyLevel);

	if (type == "basquet") {
		delta += 10;
		speed = speed * 1.8;
	}

	std::map<int, dxco::Animation*> animations = loadAnimations(model, type,
			speed);
	cocos2d::CCSprite* enemySprite = createSpriteInRandomPosition(model,
			type + "_1_0000.png", 75 + delta, 75 + delta);

	Enemy* enemy = new BombEnemy(model, enemySprite, animations, enemyLevel, type);
	//FIXME add SpeedyEnemy

	if (type == "basquet") {
		enemy->speed = speed;
	}

	addEnemy(model, enemy);
}

void EnemyFactory::createNoobSaibot(GameModel* model) {
	if (model->enemies.size() > MAX_CONCURRENT_ZOMBIES) {
		model->level->totalEnemies -= 1;
		return;
	}

	Enemy *enemy = this->getEnemy(model, this->createTypesVector(false));
	enemy->baseColor = cocos2d::ccc3(20, 30, 20);
	enemy->getSprite()->setColor(cocos2d::ccc3(20, 30, 20));
	enemy->getSprite()->setOpacity(150);

	addEnemy(model, enemy);
}

void EnemyFactory::createEnemy(GameModel* model) {
	this->createEnemy(model, this->createTypesVector(false));
}

void EnemyFactory::createBoss(GameModel* model, std::vector<std::string> types) {
	if (model->enemies.size() > MAX_CONCURRENT_ZOMBIES) {
		model->level->totalEnemies -= 1;
		return;
	}
	std::string type = "elvis";

	if (types.size() != 0) {
		type = types[rand() % types.size()];
	}

	int enemyLevel = model->prop->get("enemy.level");
	std::map<int, dxco::Animation*> animations = loadAnimations(model, type, Enemy::getSpeed(enemyLevel));

	cocos2d::CCSprite* enemySprite = createSpriteInRandomPosition(model, type + "_1_0000.png", 150, 150);
	Enemy* enemy = new Boss(model, enemySprite, animations, enemyLevel, type);
	addEnemy(model, enemy);

	SpriteUtil::fadeIn(enemy->getSprite());
}

void EnemyFactory::createSuperBoss(GameModel* model, std::vector<std::string> types) {
	std::string type = "elvis";

	if (types.size() != 0) {
		type = types[rand() % types.size()];
	}

	int enemyLevel = model->prop->get("enemy.level");
	std::map<int, dxco::Animation*> animations = loadAnimations(model, type, Enemy::getSpeed(enemyLevel));

	cocos2d::CCSprite* enemySprite = createSpriteInRandomPosition(model, type + "_1_0000.png", 280, 280);
	Enemy* enemy = new SuperBoss(model, enemySprite, animations, enemyLevel, type);
	addEnemy(model, enemy);

	SpriteUtil::fadeIn(enemy->getSprite());
}

void EnemyFactory::addEnemy(GameModel* model, Enemy* enemy) {

	model->enemies.push_back(enemy);
	model->items.push_back(enemy);
	model->mapa->addChild(enemy->getSprite());
}

std::vector<std::string> EnemyFactory::createTypesVector(bool includeElvis) {
	std::vector<std::string> vec;
	vec.push_back("campesino");
	vec.push_back("oficinista");
	vec.push_back("basquet");
	vec.push_back("cirujano");
	vec.push_back("cura");

	if (includeElvis) {
		vec.push_back("elvis");
	}

	return vec;
}

std::map<int, dxco::Animation*> EnemyFactory::loadAnimations(GameModel* model, std::string type, float speed) {
	float speedFactor = speed / Enemy::getSpeed(1);
	float frameTime = 30 / (1000 * speedFactor);

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

		std::vector<cocos2d::CCSpriteFrame*> texturesBlood;
		std::string bloodType = "sangre" + dxco::StringUtil::toString(rand() % 2 + 1) + "_";
		for (int j = 0; j < 31; j++) {
			std::string index = dxco::StringUtil::padLeft(j, 4);
			texturesBlood.push_back(dxco::SpriteUtil::createSpriteFrame(bloodType + index +".png"));
		}
		animation = new Animation(texturesBlood, 0.015, false); //don't repeat
		animations[Enemy::ENEMY_DEAD * ENEMY_ANGLE_POSITIONS + i] = animation;
	}

	return animations;
}

std::map<int, dxco::Animation*> EnemyFactory::pandaAnimations(GameModel* model) {
	float frameTime = 0.03;
	int angles = 16;

	std::map<int, dxco::Animation*> animations;

	for (int i = 0; i < angles; i++) {
		std::vector<cocos2d::CCSpriteFrame*> texturesStanding;
		texturesStanding.push_back(dxco::SpriteUtil::createSpriteFrame("herida1_" + dxco::StringUtil::toString(i + 1) + "_0000.png"));

		dxco::Animation* animation = new Animation(texturesStanding, frameTime);
		animations[Enemy::ENEMY_STANDING * angles + i] = animation;

		std::vector<cocos2d::CCSpriteFrame*> texturesWalking;

		for (int j = 0; j < 14; j++){
			std::string index = dxco::StringUtil::padLeft(j, 4);

			texturesWalking.push_back(dxco::SpriteUtil::createSpriteFrame("caminata_" + dxco::StringUtil::toString(i + 1) + "_" + index + ".png"));
		}

		animation = new Animation(texturesWalking, frameTime);
		animations[Enemy::ENEMY_WALKING * angles + i] = animation;

		std::vector<cocos2d::CCSpriteFrame*> texturesBlood;
		std::string bloodType = "sangre" + dxco::StringUtil::toString(rand() % 2 + 1) + "_";
		for (int j = 0; j < 31; j++) {
			std::string index = dxco::StringUtil::padLeft(j, 4);
			texturesBlood.push_back(dxco::SpriteUtil::createSpriteFrame(bloodType + index +".png"));
		}
		animation = new Animation(texturesBlood, 0.015, false); //don't repeat
		animations[Enemy::ENEMY_DEAD * angles + i] = animation;
	}

	return animations;
}

cocos2d::CCSprite* EnemyFactory::createSpriteInRandomPosition(GameModel* model, std::string texture, int width, int height) {

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	//create sprite
	float x, y;
	bool selected = false;
	while (!selected) {

		switch (rand() % 4) {
		case 0: {
			//up
			x = width / 2 + rand() % int(model->mapa->getWidth() - width / 2);
			y = model->mapa->getHeight() - height / 2;
			break;
		}
		case 1: {
			//down
			x = width / 2 + rand() % int(model->mapa->getWidth() - width / 2);
			y = height / 2;
			break;
		}
		case 2: {
			//left
			x = width / 2;
			y = height / 2 + rand() % int(model->mapa->getHeight() - height / 2);
			break;
		}
		case 3: {
			//right
			x = model->mapa->getWidth() - width / 2;
			y = height / 2 + rand() % int(model->mapa->getHeight() - height / 2);
			break;
		}
		}

		float distance = MathUtil::distance(cocos2d::CCPoint(x, y), model->player->getLocation());
		selected = distance > (width / 2 + model->player->getWidth() / 2) * 1.3;
	}
	return dxco::SpriteUtil::create(texture, x, y, width, height, true);
}

}
