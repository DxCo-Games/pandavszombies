#include "GameModel.h"
#include "../HelloWorldScene.h"
#include "dxco/SpriteUtil.h"
#include <cstdlib>


namespace dxco {

GameModel::GameModel(HelloWorld* vista, Player* player) {
	this->player = player;
	player->model = this;
	this->vista = vista;
	this->items.push_back(player);
}

void GameModel::addBullet(Bullet* bullet) {
	this->bullets.push_back(bullet);
	this->vista->addChild(bullet->getSprite(), 2);
}


std::vector<Item*>& GameModel::getItems() {
	return items;
}

void GameModel::addEnemy() {
	//make random point
	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	float x, y;
	switch( rand() % 4) {
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
	cocos2d::CCSprite* enemySprite = dxco::SpriteUtil::create("citizenzombie1.png", x, y, 35, 35);

	//new enemy
	std::map<int, dxco::Animation*> animations;
	Enemy* enemy = new Enemy(this, enemySprite, animations);

	this->enemies.push_back(enemy);
	this->items.push_back(enemy);
	this->vista->addChild(enemy->getSprite());
}

void GameModel::update(float dt) {
	for (int i = 0; i < this->bullets.size(); i++) {
		Bullet* bullet = this->bullets[i];
		bullet->update(dt);

		for (int j = 0; j < this->enemies.size(); j++) {
			Enemy* enemy = this->enemies[j];

			if (!enemy->muerto) {
				bool shooted = enemy->shoot(bullet);

				if (shooted) {
					continue;
				}
			}
		}
	}

	for (int i = 0; i < this->enemies.size(); i++) {
		Enemy* enemy = this->enemies[i];
		enemy->update(dt);
	}
}

} /* namespace dxco */
