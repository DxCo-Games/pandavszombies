#include "TimedLevel.h"
#include "../../dxco/StringUtil.h"
#include "../../dxco/SpriteUtil.h"
#include "../../HelloWorldScene.h"

namespace dxco {

TimedLevel::TimedLevel(GameModel *model, std::vector<EnemyWave*>& waves, int seconds): Level(model, waves) {
	this->seconds = seconds;
	this->dt = 0;

	std::string msg = "Survive for "+ StringUtil::toString(seconds) +" seconds to win.";
	model->vista->message(msg);

	//fix timer sprite
	SpriteUtil::setTexture(model->vista->timer, "gameplay/TIMER.png");
}

bool TimedLevel::isFinished() {
	return this->dt >= this->seconds;
}

void TimedLevel::updateInterface() {
	std::string playerKillsText = StringUtil::intToKString(this->model->kills);
	this->model->vista->killsLabel->setString(playerKillsText.c_str());
	this->model->vista->setTimerLabel(this->seconds - this->dt);
}

void TimedLevel::updateFreezed(float dt) {
	updateInterface();
	this->dt += dt;
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
