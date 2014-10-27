#include "TimedLevel.h"

namespace dxco {

TimedLevel::TimedLevel(GameModel *model, std::vector<EnemyWave*>& waves, int seconds): Level(model, waves) {
	this->seconds = seconds;
	this->dt = 0;
}

bool TimedLevel::isFinished() {
	return this->dt >= this->seconds;
}

void TimedLevel::update(float dt) {
	Level::update(dt);
	this->dt += dt;
}

void TimedLevel::restartLevel() {
	Level::restartLevel();
	this->dt = 0;
}

} /* namespace dxco */
