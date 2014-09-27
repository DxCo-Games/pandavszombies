#include "Level.h"
#include "EnemyWave.h"
#include "../GameModel.h"

namespace dxco {

Level::Level(GameModel *model, std::vector<EnemyWave*>& waves) {
	// TODO Auto-generated constructor stub
	this->waves = waves;
	this->model = model;
	this->currentWave = 0;
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
	this->currentWave =0;
	this->waves[this->currentWave]->reset();
}

} /* namespace dxco */
