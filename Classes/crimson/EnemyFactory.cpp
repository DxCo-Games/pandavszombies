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
	//create sprite
	cocos2d::CCSprite* enemySprite = getRandomSprite(model, "z1/1.png", 50, 50);

	float frameTime = 0.18;

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

void EnemyFactory::createBoss(GameModel* model) {

	//create sprite
	cocos2d::CCSprite* enemySprite = getRandomSprite(model, "b/1.png", 120, 120);
	float frameTime = 0.18;

	//new enemy

	std::map<int, dxco::Animation*> animations;
	for (int i = 0; i < ENEMY_ANGLE_POSITIONS; i++) {
		std::vector<cocos2d::CCTexture2D*> texturesWalking;
		texturesWalking.push_back(dxco::SpriteUtil::createTexture("b/" + dxco::StringUtil::toString(i + 1) + ".png"));
		dxco::Animation* animation = new Animation(texturesWalking, frameTime);
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
