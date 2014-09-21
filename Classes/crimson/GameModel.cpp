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
	this->mapa = vista->mapa;

	this->player->setWeapon(Player::PISTOL);
	this->bonusFactory = new BonusFactory();
	this->playerHurt = false;
	this->freezeBonusActivated = false;

	//batch node added to map
	this->enemyFactory = new EnemyFactory();
	this->mapa->addChild(this->enemyFactory->enemySpriteSheetFront, 3);
	this->mapa->addChild(this->enemyFactory->enemySpriteSheetBack, 1);
}

void GameModel::addBullet(Bullet* bullet) {
	this->bullets.push_back(bullet);
	this->mapa->addChild(bullet->getSprite(), 2);
}


std::vector<Item*>& GameModel::getItems() {
	return items;
}

void GameModel::enemyKilled(Enemy* enemy) {
	this->player->score += enemy->score;
}

void GameModel::update(float dt) {
	this->playerHurt = false;

	if (this->player->weapon->bullets <= 0 && this->player->weaponType != Player::PISTOL) {
		this->player->setWeapon(Player::PISTOL);
	}

	this->player->update(dt);
	this->player->weapon->update(dt);

	if (!this->freezeBonusActivated) {
		this->enemyFactory->update(this, dt);
	}

	for (int i = 0; i < this->bullets.size(); i++) {
		Bullet* bullet = this->bullets[i];
		bullet->update(dt);

		for (int j = 0; j < this->enemies.size(); j++) {
			Enemy* enemy = this->enemies[j];

			if (enemy->isActive()) {
				bool shooted = enemy->shoot(bullet);

				if (shooted) {
					break;
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

	//reset positions
	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	float mapWidth = visibleSize.width * 1.5;
	float mapHeight = visibleSize.height * 1.5;
	float mapCornerX = - (mapWidth - visibleSize.width) / 2;
	float mapCornerY = - (mapHeight - visibleSize.height) / 2;
	this->mapa->moveToAbsolute(mapCornerX, mapCornerY);
	this->vista->clouds->moveToAbsolute(mapCornerX, mapCornerY);

	Enemy::ENEMY_SPEED = ENEMY_DEFAULT_SPEED;

	this->player->restartPosition();
	this->player->life = PLAYER_LIFE;
	this->player->score = 0;

	this->player->shieldActivated = false;
	this->player->movementSpeedBonus = 1;
	this->player->bulletSpeedBonus = 1;

	this->player->setWeapon(Player::PISTOL);

	this->vista->timer = 0;

	this->enemyFactory->enemySpriteSheetBack->removeAllChildren();
	this->enemyFactory->enemySpriteSheetFront->removeAllChildren();
	for (int i = 0; i < this->items.size(); i++) {
		this->mapa->removeChild(this->items[i]->getSprite());
	}
	this->items.clear();
	this->enemies.clear();

	for (int i = 0; i < this->bullets.size(); i++) {
		this->mapa->removeChild(this->bullets[i]->getSprite());
	}
	this->bullets.clear();

	for (int i = 0; i < this->bonuses.size(); i++) {
		this->mapa->removeChild(this->bonuses[i]->getSprite());
	}
	this->bonuses.clear();

	this->enemyFactory->bossDt = 0;
	this->enemyFactory->enemyDt = 0;
}


} /* namespace dxco */
