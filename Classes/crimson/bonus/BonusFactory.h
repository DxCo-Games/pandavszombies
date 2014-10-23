#ifndef BONUSFACTORY_H_
#define BONUSFACTORY_H_

#include "cocos2d.h"

namespace dxco {

class GameModel;
class Bonus;

class BonusFactory {
public:
	BonusFactory();

	void createBonus(GameModel* model, cocos2d::CCPoint);

	Bonus* createWeaponBonus(GameModel* model, cocos2d::CCPoint);
};


} /* namespace dxco */

#endif /* BONUSFACTORY_H_ */
