#include "KillCountLevel.h"
#include "../GameModel.h"
#include "../../dxco/StringUtil.h"
#include "../../HelloWorldScene.h"

namespace dxco {

KillCountLevel::KillCountLevel(GameModel *model, std::vector<EnemyWave*>& waves, int kills): Level(model, waves) {
	this->kills = kills;

	std::string msg = "Kill "+ StringUtil::toString(kills) +" zombies to win.";
	model->vista->message(msg);
}

bool KillCountLevel::isFinished() {
	return this->model->kills >= this->kills;
}

void KillCountLevel::updateInterface() {
	std::string playerKillsText = StringUtil::intToKString(this->model->kills) + "/" +
			StringUtil::intToKString(this->kills);
	this->model->vista->killsLabel->setString(playerKillsText.c_str());
}

} /* namespace dxco */
