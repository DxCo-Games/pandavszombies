#include "SurvivalLevel.h"
#include "../enemies/Enemy.h"
#include "../GameModel.h"
#include "../GameProperties.h"
#include "../../HelloWorldScene.h"
#include "../../dxco/StringUtil.h"

namespace dxco {

SurvivalLevel::SurvivalLevel(GameModel* model): Level(model, *new std::vector<EnemyWave*>) {
	this->enemyDt = 0;
	this->bossDt = 0;
	this->enemyLevelDt = 0;
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
	this->enemyLevelDt += dt;
	if (this->enemyLevelDt > SURVIVAL_ENEMY_LEVEL_DT){
		int enemyLevel = this->model->prop->get("enemy.level");
		this->model->prop->set("enemy.level",  enemyLevel + 1);
		this->enemyLevelDt = 0;
	}

	this->updateInterface();
}

void SurvivalLevel::updateInterface() {
	std::string playerKillsText = StringUtil::intToKString(this->model->kills);
	this->model->vista->killsLabel->setString(playerKillsText.c_str());
	this->model->vista->setTimerLabel(this->model->timer);
}

void SurvivalLevel::restartLevel() {

}

} /* namespace dxco */
