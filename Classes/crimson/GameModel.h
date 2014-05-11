#ifndef GAMEMODEL_H_
#define GAMEMODEL_H_

#include "cocos2d.h"
#include "Player.h"
#include "Bullet.h"
#include <vector>

#define BULLET_DT 0.15

class HelloWorld;

namespace dxco {

class GameModel {
public:
	GameModel(HelloWorld* vista, Player* player);
	Player* player;

	void addBullet(Bullet* bullet);
	std::vector<Bullet*> bullets;

	void update(float dt);
	HelloWorld* vista;
};

} /* namespace dxco */
#endif /* GAMEMODEL_H_ */
