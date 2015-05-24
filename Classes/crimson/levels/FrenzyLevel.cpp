#include "FrenzyLevel.h"
#include "../bonus/WeaponFirstBonusFactory.h"
#include "../../dxco/Language.h"

namespace dxco {

FrenzyLevel::FrenzyLevel(GameModel* model): SurvivalLevel(model, 0.05, 3) {
	this->bonusFactory = new WeaponFirstBonusFactory();
}

std::string FrenzyLevel::getLevelText() {
	return Language::get("share.frenzy");
}

} /* namespace dxco */
