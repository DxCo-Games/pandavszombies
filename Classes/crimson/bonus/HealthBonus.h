#ifndef HEALTHBONUS_H_
#define HEALTHBONUS_H_

#define LIFE_AMOUNT 25

#include "Bonus.h"
#include "../GameModel.h"

namespace dxco {

class HealthBonus: public Bonus {
public:
	HealthBonus(GameModel* model, cocos2d::CCSprite* sprite,
			std::map<int, Animation*>& animations);

	void applyBonus();
};

} /* namespace dxco */

#endif /* HEALTHBONUS_H_ */
