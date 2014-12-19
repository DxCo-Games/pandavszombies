#include "Level.h"
#include "EnemyWave.h"
#include "../GameModel.h"
#include "../../HelloWorldScene.h"
#include "../../dxco/StringUtil.h"

namespace dxco {

Level::Level(GameModel *model, std::vector<EnemyWave*>& waves) {
	this->waves = waves;
	this->model = model;
	this->currentWave = 0;

	this->totalEnemies = 0;
	for (int i=0; i < waves.size(); i++) {
		this->totalEnemies += waves[i]->total;
	}
}

void Level::updateFreezed(float dt) {
	this->updateInterface();
}

void Level::update(float dt) {
	EnemyWave *wave = this->waves[this->currentWave];
	if (!wave->isFinished()) {
		wave->update(dt);
	} else if (this->currentWave < this->waves.size() - 1) {
		//if it's not the last wave, move to the next
		this->currentWave +=1;
		this->waves[this->currentWave]->reset();
	}
	this->updateInterface();
}

bool Level::isFinished() {
	//return true if all waves are finished and all enemies were killed
	if (this->waves[this->currentWave]->isFinished() &&
			this->currentWave == this->waves.size() -1) {
		//note this waits for the blood splat to disappear.
		return this->model->enemies.size() == 0;
	}
	return false;
}

void Level::restartLevel() {
	this->currentWave = 0;
	this->waves[this->currentWave]->reset();
}

void Level::updateInterface() {
	std::string playerKillsText = StringUtil::intToKString(this->model->kills) + "/" +
			StringUtil::intToKString(this->totalEnemies);
	this->model->vista->killsLabel->setString(playerKillsText.c_str());
}

} /* namespace dxco */
