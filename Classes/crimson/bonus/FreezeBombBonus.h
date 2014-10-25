#ifndef FREEZEBOMBBONUS_H_
#define FREEZEBOMBBONUS_H_

#define FREEZE_BOMB_BONUS_DURATION 6

#include "TimeBonus.h"

namespace dxco {

class FreezeBombBonus: public TimeBonus {
public:
	FreezeBombBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);

	void applyBonus();

	void removeBonus();
};

} /* namespace dxco */

#endif /* FREEZEBOMBBONUS_H_ */
