#ifndef BONUSFACTORY_H_
#define BONUSFACTORY_H_

#include "cocos2d.h"

#define BONUS_PROBABILITY 3

namespace dxco {

class GameModel;

class BonusFactory {
public:
	BonusFactory();

	void createBonus(GameModel* model, cocos2d::CCPoint);
};

} /* namespace dxco */

#endif /* BONUSFACTORY_H_ */
