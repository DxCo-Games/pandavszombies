#ifndef GAMEMODEL_H_
#define GAMEMODEL_H_

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "Bonus.h"
#include "EnemyFactory.h"
#include "BonusFactory.h"
#include "Bullet.h"
#include <vector>

#define BOMBA_TIME 5

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
	float bombaTime;

	void restartGame();
};

} /* namespace dxco */
#endif /* GAMEMODEL_H_ */
