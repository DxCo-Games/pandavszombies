#include "GameModel.h"
#include "../HelloWorldScene.h"
#include "dxco/SpriteUtil.h"
#include <cstdlib>
#include "EnemyFactory.h"
#include "Weapon.h"
#include "Player.h"
#include <algorithm>

namespace dxco {

//Used to remove old bullets to avoid ralentization
class ShouldDeleteBullet
{
    GameModel* model;
public:
    ShouldDeleteBullet( GameModel* model ) : model( model ) {
    	cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
    	maxX = this->model->mapa->getWidth() + origin.x;
    	maxY = this->model->mapa->getHeight() + origin.y;
    	minX = origin.x;
    	minY = origin.y;
    }

    float maxX;
    float maxY;
    float minX;
    float minY;

    bool operator()( Bullet* bullet )
    {
    	if (bullet->used) {
			return true;
		}

		if(bullet->getLeftPosition() < minX ||
		   bullet->getRightPosition() > maxX ||
		   bullet->getBottomPosition() < minY ||
		   bullet->getTopPosition() > maxY) {

			this->model->mapa->removeChild(bullet->getSprite());
			return true;
		}

		return false;
    }
};

GameModel::GameModel(HelloWorld* vista, Player* player) {

	//not very nice
	this->player = player;
	player->model = this;
	this->vista = vista;

	this->player->setWeapon(Player::FIRE);
	this->mapa = vista->mapa;
	this->enemyFactory = new EnemyFactory();
	this->bonusFactory = new BonusFactory();
	this->damage = false;
}

void GameModel::addBullet(Bullet* bullet) {
	this->bullets.push_back(bullet);
	this->mapa->addChild(bullet->getSprite(), 2);
}


std::vector<Item*>& GameModel::getItems() {
	return items;
}

void GameModel::update(float dt) {
	this->damage = false;
	this->player->weapon->update(dt);
	this->player->update(dt);

	this->enemyFactory->update(this, dt);

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

	//Bullet cleanup
	this->bullets.erase(
	    std::remove_if(this->bullets.begin(), this->bullets.end(), ShouldDeleteBullet(this)),
	    				this->bullets.end());

	//if used, remove
	//if out of screen, remove
}

void GameModel::restartGame() {
	this->player->restartPosition();
	this->player->life = PLAYER_LIFE;
	this->player->setWeapon(Player::PISTOL);
	this->mapa->moveToAbsolute(0, 0);
	this->vista->clouds->moveToAbsolute(0, 0);

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
