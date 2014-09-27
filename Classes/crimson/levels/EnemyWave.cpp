#include "EnemyWave.h"
#include "../GameModel.h"

namespace dxco {

EnemyWave::EnemyWave(GameModel *model, int total, float freq, float speed, bool isBoss) {
	this->dt = 100;
	this->freq = freq;
	this->speed = speed;
	this->model = model;
	this->isBoss = isBoss;
	this->count = 0;
	this->total = total;
}

bool EnemyWave::isFinished() {
	//TODO returns true if all the enemies of this wave have been created
	return this->count == this->total;
}
void EnemyWave::update(float dt) {
	Enemy::ENEMY_SPEED = this->speed; //FIXME pass speed to the factory as parameter
	this->dt += dt;
	if (this->dt > this->freq){
		if (this->isBoss) {
			this->model->enemyFactory->createBoss(model);
		} else {
			this->model->enemyFactory->createEnemy(model);
		}
		this->dt = 0;
		this->count += 1;
	}

}

void EnemyWave::reset() {
	this->count = 0;
	this->dt = 0;
}

} /* namespace dxco */
