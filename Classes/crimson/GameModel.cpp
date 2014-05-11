#include "GameModel.h"
#include "../HelloWorldScene.h"

namespace dxco {

GameModel::GameModel(HelloWorld* vista, Player* player) {
	this->player = player;
	player->model = this;
	this->vista = vista;
}

void GameModel::addBullet(Bullet* bullet) {
	this->bullets.push_back(bullet);
	this->vista->addChild(bullet->getSprite());
}

void GameModel::update(float dt) {
	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets[i]->update(dt);
	}
}

} /* namespace dxco */
