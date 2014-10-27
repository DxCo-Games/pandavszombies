#include "KillCountLevel.h"
#include "../GameModel.h"

namespace dxco {

KillCountLevel::KillCountLevel(GameModel *model, std::vector<EnemyWave*>& waves, int kills): Level(model, waves) {
	this->kills = kills;
}

bool KillCountLevel::isFinished() {
	return this->model->kills >= this->kills;
}

} /* namespace dxco */
