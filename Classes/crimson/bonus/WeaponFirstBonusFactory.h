#ifndef WEAPONFIRSTBONUSFACTORY_H_
#define WEAPONFIRSTBONUSFACTORY_H_

#include "BonusFactory.h"

namespace dxco {

class WeaponFirstBonusFactory: public BonusFactory {
public:
	WeaponFirstBonusFactory();

	virtual void createBonus(GameModel* model, cocos2d::CCPoint);
};

} /* namespace dxco */

#endif /* WEAPONFIRSTBONUSFACTORY_H_ */
