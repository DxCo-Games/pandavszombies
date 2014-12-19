#include "KillCountLevel.h"
#include "../GameModel.h"
#include "../../dxco/StringUtil.h"
#include "../../HelloWorldScene.h"

namespace dxco {

KillCountLevel::KillCountLevel(GameModel *model, std::vector<EnemyWave*>& waves, int kills, std::string type): Level(model, waves) {
	this->kills = kills;
	this->type = type;

	std::string msg = "Kill "+ StringUtil::toString(kills) +" " + this->verboseType() + " to win.";
	model->vista->message(msg);
}

std::string KillCountLevel::verboseType() {
	if(this->type == "elvis") return "kings";
	if(this->type == "granjero") return "farmers";
	if(this->type == "cirujano") return "surgeons";
	if(this->type == "oficinista") return "office workers";
	if(this->type == "basket") return "basketball players";
	if(this->type == "cura") return "priests";
}

bool KillCountLevel::isFinished() {
	return this->model->typeKills[this->type] >= this->kills;
}

void KillCountLevel::updateInterface() {
	std::string playerKillsText = StringUtil::intToKString(this->model->typeKills[this->type]) + "/" +
			StringUtil::intToKString(this->kills);
	this->model->vista->killsLabel->setString(playerKillsText.c_str());
}

} /* namespace dxco */
