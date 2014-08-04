#ifndef GAMEMODEL_H_
#define GAMEMODEL_H_

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "Bonus.h"
#include "EnemyFactory.h"
#include "BonusFactory.h"
#include "Bullet.h"
#include "Mapa.h"
#include <vector>

class HelloWorld;

namespace dxco {

class GameModel {
public:
	GameModel(HelloWorld* vista, Player* player);
	Player* player;
	EnemyFactory* enemyFactory;
	BonusFactory* bonusFactory;

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
	bool shouldDeleteBullet(Bullet* bullet);
	bool playerHurt;
};

} /* namespace dxco */
#endif /* GAMEMODEL_H_ */
