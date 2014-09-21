#ifndef FREEZEBOMBBONUS_H_
#define FREEZEBOMBBONUS_H_

#include "TimeBonus.h"

#define FREEZE_BOMB_BONUS_DURATION 10

namespace dxco {

class FreezeBombBonus: public TimeBonus {
public:
	FreezeBombBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);

	void applyBonus();

	void removeBonus();
};

} /* namespace dxco */

#endif /* FREEZEBOMBBONUS_H_ */
