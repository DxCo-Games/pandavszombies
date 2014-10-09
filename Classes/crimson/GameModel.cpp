#include "GameModel.h"
#include "levels/Level.h"
#include "levels/SurvivalLevel.h"
#include "levels/EnemyWave.h"
#include "../HelloWorldScene.h"
#include "dxco/SpriteUtil.h"
#include <cstdlib>
#include "EnemyFactory.h"
#include "ChainedKillsManager.h"
#include "Weapon.h"
#include "Player.h"
#include "daos/UserDAO.h"
#include <algorithm>
#include "levels/LevelParser.h"

namespace dxco {

//Used to remove old bullets to avoid ralentization
class ShouldDeleteBullet
{
    GameModel* model;
public:
    ShouldDeleteBullet( GameModel* model ) : model( model ) {
    	cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
    	maxX = this->model->mapa->getWidth() + origin.x + 200;
    	maxY = this->model->mapa->getHeight() + origin.y + 200;
    	minX = origin.x - 200;
    	minY = origin.y - 200;
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

GameModel::GameModel(HelloWorld* vista, Player* player, bool survival) {

	//not very nice
	this->player = player;
	player->model = this;
	this->vista = vista;
	this->mapa = vista->mapa;

	if (survival) {
		this->level = new SurvivalLevel(this);
	} else {
		//TODO create level and waves from file. decide story/survival based on parameter
		/*EnemyWave *w1 = new EnemyWave(this, 10, 0.3, ENEMY_DEFAULT_SPEED);
		EnemyWave *w2 = new EnemyWave(this, 2, 5, ENEMY_DEFAULT_SPEED, true);
		std::vector<EnemyWave*> waves;
		waves.push_back(w1);
		waves.push_back(w2);*/
		std::vector<EnemyWave*> waves = LevelParser::parse(this, "levels/level1.json");
		this->level = new Level(this, waves);
	}


	this->player->setWeapon(Player::PISTOL);
	this->bonusFactory = new BonusFactory();
	this->playerHurt = false;
	this->freezeBonusActivated = 0;
	this->kills = 0;
	this->chains = new ChainedKillsManager(this);
	this->timer = 0;

	//batch node added to map
	this->enemyFactory = new EnemyFactory();
	this->mapa->addChild(this->enemyFactory->enemySpriteSheetFront, 3);
	this->mapa->addChild(this->enemyFactory->enemySpriteSheetBack, 1);
}

void GameModel::addBullet(Bullet* bullet) {
	this->bullets.push_back(bullet);
	this->mapa->addChild(bullet->getSprite(), 10001);
}


std::vector<Item*>& GameModel::getItems() {
	return items;
}

void GameModel::enemyKilled(Enemy* enemy) {
	this->player->score += enemy->score;
}

void GameModel::update(float dt) {
	this->timer += dt;
	this->playerHurt = false;

	this->player->update(dt);
	this->player->weapon->update(dt);

	if (!this->freezeBonusActivated) {
		this->level->update(dt);
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

	if (!this->player->isActive() || this->level->isFinished()){
		this->restartGame();
	}

	//Bullet cleanup
	this->bullets.erase(
	    std::remove_if(this->bullets.begin(), this->bullets.end(), ShouldDeleteBullet(this)),
	    				this->bullets.end());

	this->chains->updateView();
}

void GameModel::restartGame() {

	updateCoins();

	//reset positions
	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	float mapWidth = MAP_WIDTH;
	float mapHeight = MAP_HEIGHT;
	float mapCornerX = - (mapWidth - visibleSize.width) / 2;
	float mapCornerY = - (mapHeight - visibleSize.height) / 2;
	this->mapa->moveToAbsolute(mapCornerX, mapCornerY);
	this->vista->clouds->moveToAbsolute(mapCornerX, mapCornerY);

	Enemy::ENEMY_SPEED = ENEMY_DEFAULT_SPEED;

	this->player->restartPosition();
	this->player->life = PLAYER_LIFE;
	this->vista->weaponBar->setPercentage(100);
	this->vista->bonus1->stopAllActions();
	this->vista->bonus1->setOpacity(0);
	this->vista->bonus2->stopAllActions();
	this->vista->bonus2->setOpacity(0);
	this->player->score = 0;
	this->player->weaponBonus = 0;

	this->player->shieldActivated = 0;
	this->player->movementSpeedBonus = 1;
	this->player->weaponSpeedBonus = 1;
	this->kills = 0;
	this->chains->restart();
	this->timer = 0;

	this->player->setWeapon(Player::PISTOL);


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
	this->level->restartLevel();
}

void GameModel::updateCoins() {
	int coins = this->player->score / COIN_VALUE;

	UserDAO::addCoins(coins);
}


} /* namespace dxco */
