#ifndef GAMEMODEL_H_
#define GAMEMODEL_H_

#include "cocos2d.h"
#include "Player.h"
#include "enemies/Enemy.h"
#include "bonus/Bonus.h"
#include "enemies/EnemyFactory.h"
#include "bonus/BonusFactory.h"
#include "Bullet.h"
#include "Mapa.h"
#include <vector>

#define COIN_VALUE 100
#define MAP_WIDTH 623
#define MAP_HEIGHT 516

class HelloWorld;

namespace dxco {

class Level;
class ChainedKillsManager;
class GameProperties;
class VoiceManager;

class GameModel {
public:
	GameModel(HelloWorld* vista, Player* player);
	void loadLevel(bool survival, bool frenzy, int level=-1);
	int levelNumber;
	Player* player;
	EnemyFactory* enemyFactory;
	Level *level;
	ChainedKillsManager *chains;
	VoiceManager *voice;
	GameProperties *prop;

	void addBullet(Bullet* bullet);
	std::vector<Bullet*> bullets;

	std::vector<Item*>& getItems();
	std::vector<Item*> items;
	std::vector<Enemy*> enemies;
	std::vector<Bonus*> bonuses;

	void update(float dt);
	float timer;
	HelloWorld* vista;
	Mapa* mapa;
	void restartGame();
	void enemyKilled(Enemy* enemy);
	bool shouldDeleteBullet(Bullet* bullet);
	bool playerHurt;
	int freezeBonusActivated;
	int kills;
	std::map<std::string,int> typeKills;
	void resetTypeKills();

	void updateAds(float dt);

	bool adShowed;
	float adDt;

	bool showAd();
private:
	void updateCoins();
	int getLevelStars();
};

} /* namespace dxco */
#endif /* GAMEMODEL_H_ */
