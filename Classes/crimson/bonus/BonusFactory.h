#ifndef BONUSFACTORY_H_
#define BONUSFACTORY_H_

#include "cocos2d.h"

#define MAX_CONCURRENT_BONUS 10
#define MAX_CONCURRENT_WEAPONS 3

namespace dxco {

class GameModel;
class Bonus;

class BonusFactory {
public:
	BonusFactory();

	virtual void createBonus(GameModel* model, cocos2d::CCPoint);
	void addToMap(GameModel* model, Bonus* bonus);

	Bonus* createWeaponBonus(GameModel* model, cocos2d::CCPoint);

	int countWeaponBonus(GameModel* model);
	int countFreezeBonus(GameModel* model);
};


} /* namespace dxco */

#endif /* BONUSFACTORY_H_ */
