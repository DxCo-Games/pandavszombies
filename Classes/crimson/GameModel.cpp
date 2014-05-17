#include "GameModel.h"
#include "../HelloWorldScene.h"
#include "dxco/SpriteUtil.h"
#include <cstdlib>
#include "EnemyFactory.h"
#include "Bomba.h"
#include "Weapon.h"
#include "Player.h"

namespace dxco {

GameModel::GameModel(HelloWorld* vista, Player* player) {

	//not very nice
	this->player = player;
	player->model = this;
	this->player->setWeapon(Player::PISTOL);

	this->vista = vista;
	this->mapa = vista->mapa;
	this->bombaTime = 0;
	this->enemyFactory = new EnemyFactory();
	this->bonusFactory = new BonusFactory();
}

void GameModel::addBullet(Bullet* bullet) {
	this->bullets.push_back(bullet);
	this->mapa->addChild(bullet->getSprite(), 2);
}


std::vector<Item*>& GameModel::getItems() {
	return items;
}

void GameModel::update(float dt) {
	this->player->weapon->update(dt);
	this->bombaTime+= dt;
	this->enemyFactory->update(this, dt);

	if (this->bombaTime > BOMBA_TIME) {
		Bomba* bomba = new Bomba(this);

		bomba->explode(10 + (rand() % 5));
		this->bombaTime = 0;
	}

	for (int i = 0; i < this->bullets.size(); i++) {
		Bullet* bullet = this->bullets[i];
		bullet->update(dt);

		for (int j = 0; j < this->enemies.size(); j++) {
			Enemy* enemy = this->enemies[j];

			if (enemy->isActive()) {
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

	for (int i = 0; i < this->bonuses.size(); i++) {
		this->bonuses[i]->update(dt);
	}

	if (!this->player->isActive()){
		this->restartGame();
	}
}

void GameModel::restartGame() {
	this->player->restartPosition();
	this->player->life = PLAYER_LIFE;
	this->player->setWeapon(Player::PISTOL);

	for (int i = 0; i < this->items.size(); i++) {
		this->items[i]->getSprite()->setVisible(false);
	}
	this->items.clear();
	this->enemies.clear();

	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets[i]->getSprite()->setVisible(false);
	}
	this->bullets.clear();

	for (int i = 0; i < this->bonuses.size(); i++) {
		this->bonuses[i]->getSprite()->setVisible(false);
	}
	this->bonuses.clear();

	this->enemyFactory->bossDt = 0;
	this->enemyFactory->enemyDt = 0;
}

} /* namespace dxco */
