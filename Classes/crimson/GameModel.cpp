#include "GameModel.h"
#include "GameProperties.h"
#include "levels/Level.h"
#include "levels/SurvivalLevel.h"
#include "levels/FrenzyLevel.h"
#include "levels/LevelParser.h"
#include "levels/TutorialLevel.h"
#include "../HelloWorldScene.h"
#include "dxco/SpriteUtil.h"
#include "dxco/StringUtil.h"
#include "dxco/VoiceManager.h"
#include <cstdlib>
#include "enemies/EnemyFactory.h"
#include "ChainedKillsManager.h"
#include "Weapon.h"
#include "Player.h"
#include "daos/UserDAO.h"
#include <algorithm>
#include "SimpleAudioEngine.h"
#include "bonus/WeaponFirstBonusFactory.h"
#include "enemies/Enemy.h"

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
			delete bullet;
			return true;
		}

		return false;
    }
};

GameModel::GameModel(HelloWorld* vista, Player* player) {
	this->prop = new GameProperties();
	//not very nice
	this->player = player;
	player->model = this;
	player->life = this->prop->get("player.life");
	this->vista = vista;
	this->mapa = vista->mapa;

	this->player->setWeapon(Player::PISTOL);
	this->voice = new VoiceManager();
	this->voice->loadRandom("voices/dead.ogg");
	this->voice->loadRandom("voices/talkin.ogg");
	this->voice->loadRandom("voices/brains1.ogg");
	this->voice->loadRandom("voices/brains2.ogg");
	this->voice->loadRandom("voices/chiau.ogg");
	this->playerHurt = false;
	this->freezeBonusActivated = 0;
	this->kills = 0;
	this->chains = new ChainedKillsManager(this);
	this->timer = 0;
	this->level = 0;
	this->levelNumber = 0;
	//se puede evitar esto?
	this->resetTypeKills();

	//batch node added to map
	this->enemyFactory = new EnemyFactory();
}

void GameModel::resetTypeKills() {
	this->typeKills["elvis"] = 0;
	this->typeKills["oficinista"] = 0;
	this->typeKills["campesino"] = 0;
	this->typeKills["cirujano"] = 0;
	this->typeKills["cura"] = 0;
	this->typeKills["basket"] = 0;
}

void GameModel::loadLevel(bool survival, bool frenzy, int level) {
	this->levelNumber = level;
	if (survival) {
		this->level = new SurvivalLevel(this);
	} else if (frenzy) {
		this->level = new FrenzyLevel(this);
	} else if (level == 1){
		this->level = new TutorialLevel(this);
	} else if (level == 100){
		this->level = new SurvivalLevel(this);
		this->level->title = "The mystery level";
		this->vista->setMap(1);
	} else {
		this->level = LevelParser::parse(this, "levels/level" + StringUtil::toString(level) +".json", level);
	}
}

void GameModel::addBullet(Bullet* bullet) {
	//FIXME shouldn't this be in the weapon?
	this->bullets.push_back(bullet);
	this->mapa->addChild(bullet->getSprite(), 10001);
}


std::vector<Item*>& GameModel::getItems() {
	return items;
}

void GameModel::enemyKilled(Enemy* enemy) {
	this->player->score += enemy->score;

	cocos2d::CCPoint location = enemy->getLocation();
	this->kills += 1;
	this->typeKills[enemy->type]++;
	this->chains->addKill();

	this->level->bonusFactory->createBonus(this, cocos2d::CCPoint(location.x,
			location.y - enemy->getHeight() / 2));
}

void GameModel::update(float dt) {

	this->timer += dt;
	this->playerHurt = false;

	this->player->update(dt);
	this->player->weapon->update(dt);
	this->voice->update(dt);

	if (this->freezeBonusActivated) {
		this->level->updateFreezed(dt);
	} else {
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

	if (this->level->isFinished() || !this->player->isActive()) {
		this->vista->hideControls();
		this->vista->juegoPausado = true;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		this->vista->opacityLayer->setVisible(true);
		int stars = this->getLevelStars();
		this->vista->levelFinishedLayer->show(this->player->score, this->kills, this->player->score / COIN_VALUE, stars);
		updateCoins();

		if (this->level->isFinished()) {
			this->vista->playEffect("sounds/youwin2.ogg");
			UserDAO::finishLevel(this->levelNumber, stars);
		}
	}

	//Bullet cleanup
	this->bullets.erase(
	    std::remove_if(this->bullets.begin(), this->bullets.end(), ShouldDeleteBullet(this)),
	    				this->bullets.end());

	this->chains->updateView();
}

int GameModel::getLevelStars() {
	if (!this->player->isActive()){
		return 0;
	}
	if (this->player->life == this->prop->get("player.life")) {
		return 3;
	} else if (this->player->life > 0.75 * this->prop->get("player.life")) {
		return 2;
	}
	return 1;
}

void GameModel::restartGame() {

	//reset positions
	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	float mapWidth = MAP_WIDTH;
	float mapHeight = MAP_HEIGHT;
	float mapCornerX = - (mapWidth - visibleSize.width) / 2;
	float mapCornerY = - (mapHeight - visibleSize.height) / 2;

	this->mapa->moveToAbsolute(mapCornerX, mapCornerY);
	this->vista->clouds->moveToAbsolute(mapCornerX, mapCornerY);
	this->vista->opacityLayer->setVisible(false);
	this->vista->bubble->setVisible(false);

	this->prop->set("enemy.level", 1);

	this->player->restartPosition();
	this->player->life = this->prop->get("player.life");
	this->vista->weaponBar->setPercentage(100);
	this->vista->bonus1->stopAllActions();
	this->vista->bonus1->setOpacity(0);
	this->vista->bonus2->stopAllActions();
	this->vista->bonus2->setOpacity(0);
	this->player->score = 0;
	this->player->weaponBonus = 0;
	this->freezeBonusActivated = 0;

	this->player->shieldActivated = 0;
	this->player->movementSpeedBonus = 1;
	this->player->weaponSpeedBonus = 1;
	this->kills = 0;
	this->resetTypeKills();
	this->chains->restart();
	this->timer = 0;

	this->player->setWeapon(Player::PISTOL);

	for (int i = 0; i < this->items.size(); i++) {
		this->mapa->removeChild(this->items[i]->getSprite());
	}

	for (int i = 0; i < this->bullets.size(); i++) {
		this->mapa->removeChild(this->bullets[i]->getSprite());
	}

	for (int i = 0; i < this->bonuses.size(); i++) {
		this->mapa->removeChild(this->bonuses[i]->getSprite());
	}

	this->level->restartLevel();
	this->vista->levelFinishedLayer->hide();
	this->vista->showControls();
	this->vista->juegoPausado = false;
	this->vista->pauseLayer->hide();

	this->items.clear();
	this->enemies.clear();
	this->bonuses.clear();
	this->bullets.clear();
}

void GameModel::updateCoins() {
	int coins = this->player->score / COIN_VALUE;

	UserDAO::addCoins(coins);
}


} /* namespace dxco */
