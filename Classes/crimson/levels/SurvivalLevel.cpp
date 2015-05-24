#include "SurvivalLevel.h"
#include "../enemies/Enemy.h"
#include "../GameModel.h"
#include "../GameProperties.h"
#include "../../HelloWorldScene.h"
#include "../../dxco/StringUtil.h"
#include "../../dxco/Language.h"
#include <cstdlib>

namespace dxco {

SurvivalLevel::SurvivalLevel(GameModel* model, float maxEnemyDt, float maxBossDt): Level(model, *new std::vector<EnemyWave*>) {
	this->enemyDt = 0;
	this->bossDt = 0;
	this->enemyLevelDt = 0;
	this->maxEnemyDt = maxEnemyDt;
	this->maxBossDt = maxBossDt;

	model->vista->setMap(rand() %2);
	model->prop->set("enemy.level", ZOMBIE_SURVIVAL_INITIAL_LEVEL);
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
	int enemyLevel = this->model->prop->get("enemy.level");

	if (enemyLevel <= 50) {
		if (this->enemyLevelDt > SURVIVAL_ENEMY_LEVEL_DT_BEFORE_50){
			this->model->prop->set("enemy.level",  enemyLevel + 1);
			this->enemyLevelDt = 0;
		}
	} else {
		if (this->enemyLevelDt > SURVIVAL_ENEMY_LEVEL_DT_AFTER_50){
			this->model->prop->set("enemy.level",  enemyLevel + 1);
			this->enemyLevelDt = 0;
		}
	}


	this->updateInterface();
}

bool SurvivalLevel::showAdd() {
	return (rand() % 100) < 20;
}

std::string SurvivalLevel::getLevelText() {
	return Language::get("share.survival");
}

void SurvivalLevel::updateInterface() {
	std::string playerKillsText = StringUtil::intToKString(this->model->kills);
	this->model->vista->killsLabel->setString(playerKillsText.c_str());
	this->model->vista->setTimerLabel(this->model->timer);
}

void SurvivalLevel::restartLevel() {

}

void SurvivalLevel::showMessage() {

}

} /* namespace dxco */
