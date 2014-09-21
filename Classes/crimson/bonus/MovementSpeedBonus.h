#ifndef MOVEMENTSPEEDBONUS_H_
#define MOVEMENTSPEEDBONUS_H_

#define MOVEMENT_BONUS_RATE 1.50
#define MOVEMENT_SPEED_BONUS_DURATION 10

#include "TimeBonus.h"

namespace dxco {

class MovementSpeedBonus: public TimeBonus {
public:
	MovementSpeedBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);

	void applyBonus();

	void removeBonus();
};

} /* namespace dxco */

#endif /* MOVEMENTSPEEDBONUS_H_ */
