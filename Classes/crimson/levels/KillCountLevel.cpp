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

} /* namespace dxco */
