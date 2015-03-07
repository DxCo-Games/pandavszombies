#include "KillCountLevel.h"
#include "../GameModel.h"
#include "../../dxco/StringUtil.h"
#include "../../dxco/SpriteUtil.h"
#include "../../HelloWorldScene.h"
#include "cocos2d.h"

namespace dxco {

KillCountLevel::KillCountLevel(GameModel *model, std::vector<EnemyWave*>& waves, int kills, std::string type, std::string title): Level(model, waves, title) {
	this->kills = kills;
	this->type = type;

	showMessage();
}

void KillCountLevel::showMessage() {
	std::string msg = "Kill "+ StringUtil::toString(this->kills) + " to win";
	std::string index = this->getTypeIndex();

	model->vista->message(msg, 10, SpriteUtil::create(this->type + "_" + index + "_0000" + ".png", 0, 0, 40, 40, true));
}


std::string KillCountLevel::getTypeIndex() {

	return "6";
}

std::string KillCountLevel::verboseType() {
	if(this->type == "elvis") return "kings";
	if(this->type == "campesino") return "farmers";
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
