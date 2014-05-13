#include "GameModel.h"
#include "../HelloWorldScene.h"
#include "dxco/SpriteUtil.h"
#include <cstdlib>


namespace dxco {

GameModel::GameModel(HelloWorld* vista, Player* player) {
	this->player = player;
	player->model = this;
	this->vista = vista;
}

void GameModel::addBullet(Bullet* bullet) {
	this->bullets.push_back(bullet);
	this->vista->addChild(bullet->getSprite());
}

void GameModel::addEnemy() {
	//maybe this should be in scenes update
	//create sprite
	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	cocos2d::CCSprite* enemySprite = dxco::SpriteUtil::create("citizenzombie1.png", rand() % int(visibleSize.width), rand() % int(visibleSize.height), 35, 35);

	//new enemy
	std::map<int, dxco::Animation*> animations;
	Enemy* enemy = new Enemy(this, enemySprite, animations);

	this->enemies.push_back(enemy);
	this->vista->addChild(enemy->getSprite());
}

void GameModel::update(float dt) {
	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets[i]->update(dt);
	}

	for (int i = 0; i < this->enemies.size(); i++) {
			this->enemies[i]->update(dt);
		}
}

} /* namespace dxco */
