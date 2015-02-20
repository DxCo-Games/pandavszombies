#ifndef BOMBBONUSFACTORY_H_
#define BOMBBONUSFACTORY_H_

#include "BonusFactory.h"

namespace dxco {

class BombBonusFactory: public dxco::BonusFactory {
public:
	BombBonusFactory();

	void createBonus(GameModel* model, cocos2d::CCPoint location);
};

} /* namespace dxco */

#endif /* BOMBBONUSFACTORY_H_ */
