#include "SurvivalLevel.h"
#include "../enemies/Enemy.h"
#include "../GameModel.h"
#include "../GameProperties.h"
#include "../../HelloWorldScene.h"
#include "../../dxco/StringUtil.h"
#include <cstdlib>

namespace dxco {

SurvivalLevel::SurvivalLevel(GameModel* model, float maxEnemyDt, float maxBossDt): Level(model, *new std::vector<EnemyWave*>) {
	this->enemyDt = 0;
	this->bossDt = 0;
	this->enemyLevelDt = 0;
	this->maxEnemyDt = maxEnemyDt;
	this->maxBossDt = maxBossDt;

	model->vista->setMap(rand() %2);
}

bool SurvivalLevel::isFinished() {
	return false;
}
void SurvivalLevel::update(float dt) {
	this->enemyDt += dt;
	if (this->enemyDt > maxEnemyDt){
		this->model->enemyFactory->createEnemy(this->model);
		this->enemyDt = 0;
	}

	this->bossDt += dt;
	if (this->bossDt > maxBossDt){
		this->model->enemyFactory->createBoss(this->model);
		this->bossDt = 0;
	}
	this->enemyLevelDt += dt;
	if (this->enemyLevelDt > SURVIVAL_ENEMY_LEVEL_DT){
		int enemyLevel = this->model->prop->get("enemy.level");
		this->model->prop->set("enemy.level",  enemyLevel + 1);
		this->enemyLevelDt = 0;
	}

	this->updateInterface();
}

bool SurvivalLevel::showAdd() {
	return (rand() % 100) < 20;
}

void SurvivalLevel::updateInterface() {
	std::string playerKillsText = StringUtil::intToKString(this->model->kills);
	this->model->vista->killsLabel->setString(playerKillsText.c_str());
	this->model->vista->setTimerLabel(this->model->timer);
}

void SurvivalLevel::restartLevel() {

}

} /* namespace dxco */
