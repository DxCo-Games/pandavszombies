#ifndef BONUSSHIELD_H_
#define BONUSSHIELD_H_

#include "TimeBonus.h"

#define SHIELD_BONUS_DURATION 10

namespace dxco {

class ShieldBonus: public dxco::TimeBonus {
public:
	ShieldBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);

	void applyBonus();

	void removeBonus();
};

} /* namespace dxco */

#endif /* BONUSSHIELD_H_ */
