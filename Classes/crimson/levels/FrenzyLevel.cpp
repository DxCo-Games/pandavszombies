#include "FrenzyLevel.h"
#include "../bonus/WeaponFirstBonusFactory.h"

namespace dxco {

FrenzyLevel::FrenzyLevel(GameModel* model): SurvivalLevel(model, 0.05, 3) {
	this->bonusFactory = new WeaponFirstBonusFactory();
}

} /* namespace dxco */
