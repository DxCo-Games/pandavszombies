#include "EnemyWave.h"
#include "../GameModel.h"
#include "../GameProperties.h"

namespace dxco {

EnemyWave::EnemyWave(GameModel *model, int total, float freq, int level, std::vector<std::string> types, int isBoss) {
	this->dt = 100;
	this->freq = freq;
	this->level = level;
	this->model = model;
	this->isBoss = isBoss;
	this->count = 0;
	this->total = total;
	this->types = types;
	this->killsType = "";
	this->killsFreq = 0.2;
}


EnemyWave::EnemyWave(GameModel *model, int total, float freq, int level, std::vector<std::string> types, std::string killsType, float killsFreq) {
	this->dt = 100;
	this->freq = freq;
	this->level = level;
	this->model = model;
	this->isBoss = 0;
	this->count = 0;
	this->total = total;
	this->killsType = killsType;
	this->killsFreq = killsFreq;
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
		if (this->isBoss == 1) {
			this->model->enemyFactory->createBoss(model, this->types);
		} else if (this->isBoss == 2){
			this->model->enemyFactory->createSuperBoss(model, this->types);
		} else if (this->isBoss == -1){
			this->model->enemyFactory->createPanda(model);
		} else if (this->isBoss == -2){
			this->model->enemyFactory->createNoobSaibot(model);
		} else if (this->isBoss == -3){
			this->model->enemyFactory->createPandaBoss(model);
		} else if (this->isBoss == 3){
			this->model->enemyFactory->createBombEnemy(model);
		} else {
			if (this->killsType != ""){
				this->model->enemyFactory->createEnemy(model, this->types, this->killsType, this->killsFreq);
			} else if (this->types.size()) {
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
