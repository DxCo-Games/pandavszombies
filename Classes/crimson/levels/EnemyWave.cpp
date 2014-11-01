#include "EnemyWave.h"
#include "../GameModel.h"
#include "../GameProperties.h"

namespace dxco {

EnemyWave::EnemyWave(GameModel *model, int total, float freq, int level, std::vector<std::string> types, bool isBoss) {
	this->dt = 100;
	this->freq = freq;
	this->level = level;
	this->model = model;
	this->isBoss = isBoss;
	this->count = 0;
	this->total = total;
	this->types = types;
}

bool EnemyWave::isFinished() {
	//returns true if all the enemies of this wave have been created
	return this->count == this->total;
}
void EnemyWave::update(float dt) {
	this->model->prop->set("enemy.level", this->level);
	this->dt += dt;
	if (this->dt > this->freq){
		if (this->isBoss) {
			this->model->enemyFactory->createBoss(model);
		} else {
			if (this->types.size()) {
				this->model->enemyFactory->createEnemy(model, this->types);
			} else {
				this->model->enemyFactory->createEnemy(model);
			}
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
