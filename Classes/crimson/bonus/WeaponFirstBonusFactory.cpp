#include "WeaponFirstBonusFactory.h"
#include "../GameModel.h"

namespace dxco {

WeaponFirstBonusFactory::WeaponFirstBonusFactory(): BonusFactory() {
}

void WeaponFirstBonusFactory::createBonus(GameModel* model, cocos2d::CCPoint point) {
	if (model->kills == 1) {
		Bonus* bonus = this->createWeaponBonus(model, point);
		this->addToMap(model, bonus);
	} else {
		BonusFactory::createBonus(model, point);
	}
}

} /* namespace dxco */
