#ifndef BULLETSPEEDBONUS_H_
#define BULLETSPEEDBONUS_H_

#include "TimeBonus.h"

#define WEAPON_SPEED_BONUS_DURATION 10
#define WEAPON_SPEED_BONUS_RATIO 0.4

namespace dxco {

class WeaponSpeedBonus: public TimeBonus {
public:
	WeaponSpeedBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);

	void applyBonus();

	void removeBonus();
};

} /* namespace dxco */

#endif /* BULLETSPEEDBONUS_H_ */
