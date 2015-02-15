#include "TimedLevel.h"
#include "../../dxco/StringUtil.h"
#include "../../dxco/SpriteUtil.h"
#include "../../HelloWorldScene.h"

namespace dxco {

TimedLevel::TimedLevel(GameModel *model, std::vector<EnemyWave*>& waves, int seconds, std::string title): Level(model, waves, title) {
	this->seconds = seconds;
	this->dt = 0;

	showMessage();

	//fix timer sprite
	SpriteUtil::setTexture(model->vista->timer, "gameplay/TIMER.png");
}

void TimedLevel::showMessage() {
	std::string msg = "Survive for "+ StringUtil::toString(this->seconds) + " seconds to win.";
	model->vista->message(msg);
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
