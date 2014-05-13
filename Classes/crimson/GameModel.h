#ifndef GAMEMODEL_H_
#define GAMEMODEL_H_

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>

#define BULLET_DT 0.15
#define ENEMY_DT 0.75

class HelloWorld;

namespace dxco {

class GameModel {
public:
	GameModel(HelloWorld* vista, Player* player);
	Player* player;

	void addBullet(Bullet* bullet);
	std::vector<Bullet*> bullets;

	void addEnemy();
	std::vector<Item*>& getItems();
	std::vector<Item*> items;
	std::vector<Enemy*> enemies;

	void update(float dt);
	HelloWorld* vista;
};

} /* namespace dxco */
#endif /* GAMEMODEL_H_ */
