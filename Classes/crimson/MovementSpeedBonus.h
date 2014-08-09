#ifndef HEALTHBONUS_H_
#define HEALTHBONUS_H_

#define MOVEMENT_BONUS_RATE 1.25

#include "Bonus.h"

namespace dxco {

class MovementSpeedBonus: public Bonus {
public:
	MovementSpeedBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);

	void applyBonus();
};

} /* namespace dxco */

#endif /* HEALTHBONUS_H_ */
