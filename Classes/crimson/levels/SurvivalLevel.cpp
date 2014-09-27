#include "SurvivalLevel.h"
#include "../Enemy.h"
#include "../GameModel.h"

namespace dxco {

SurvivalLevel::SurvivalLevel(GameModel* model): Level(model, *new std::vector<EnemyWave*>) {
	this->enemyDt = 0;
	this->bossDt = 0;
	this->speedDt = 0;
}

bool SurvivalLevel::isFinished() {
	return false;
}
void SurvivalLevel::update(float dt) {
	this->enemyDt += dt;
	if (this->enemyDt > SURVIVAL_ENEMY_DT){
		this->model->enemyFactory->createEnemy(this->model);
		this->enemyDt = 0;
	}

	this->bossDt += dt;
	if (this->bossDt > SURVIVAL_BOSS_DT){
		this->model->enemyFactory->createBoss(this->model);
		this->bossDt = 0;
	}
	this->speedDt += dt;
	if (this->speedDt > SURVIVAL_SPEED_DT){
		Enemy::ENEMY_SPEED = 1.1 * Enemy::ENEMY_SPEED;
		this->speedDt = 0;
	}
}

void SurvivalLevel::restartLevel() {

}

} /* namespace dxco */
