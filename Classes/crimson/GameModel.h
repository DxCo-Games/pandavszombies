#ifndef GAMEMODEL_H_
#define GAMEMODEL_H_

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "bonus/Bonus.h"
#include "EnemyFactory.h"
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

class GameModel {
public:
	GameModel(HelloWorld* vista, Player* player);
	Player* player;
	EnemyFactory* enemyFactory;
	BonusFactory* bonusFactory;
	Level *level;

	void addBullet(Bullet* bullet);
	std::vector<Bullet*> bullets;

	std::vector<Item*>& getItems();
	std::vector<Item*> items;
	std::vector<Enemy*> enemies;
	std::vector<Bonus*> bonuses;

	void update(float dt);
	HelloWorld* vista;
	Mapa* mapa;
	void restartGame();
	void enemyKilled(Enemy* enemy);
	bool shouldDeleteBullet(Bullet* bullet);
	bool playerHurt;
	bool freezeBonusActivated;
private:
	void updateCoins();
};

} /* namespace dxco */
#endif /* GAMEMODEL_H_ */
