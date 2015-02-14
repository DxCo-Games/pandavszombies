#ifndef NOBONUSFACTORY_H_
#define NOBONUSFACTORY_H_

#include "BonusFactory.h"

namespace dxco {

class NoBonusFactory: public BonusFactory {
public:
	NoBonusFactory();
	virtual void createBonus(GameModel* model, cocos2d::CCPoint);
};

} /* namespace dxco */

#endif /* NOBONUSFACTORY_H_ */
