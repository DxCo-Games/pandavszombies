#include "TimedLevel.h"
#include "../../dxco/StringUtil.h"
#include "../../HelloWorldScene.h"

namespace dxco {

TimedLevel::TimedLevel(GameModel *model, std::vector<EnemyWave*>& waves, int seconds): Level(model, waves) {
	this->seconds = seconds;
	this->dt = 0;

	std::string msg = "Survive for "+ StringUtil::toString(seconds) +" seconds to win.";
	model->vista->message(msg);
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
