#include "GameModel.h"
#include "../HelloWorldScene.h"
#include "dxco/SpriteUtil.h"
#include <cstdlib>
#include "GameFactory.h"

namespace dxco {

GameModel::GameModel(HelloWorld* vista, Player* player) {
	this->player = player;
	player->model = this;
	this->vista = vista;
}

void GameModel::addBullet(Bullet* bullet) {
	this->bullets.push_back(bullet);
	this->vista->addChild(bullet->getSprite(), 2);
}


std::vector<Item*>& GameModel::getItems() {
	return items;
}

void GameModel::addEnemy() {

	Enemy* enemy = GameFactory::createEnemy(this);

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
