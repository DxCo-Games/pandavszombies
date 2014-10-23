#ifndef EXPLOSIONBONUS_H_
#define EXPLOSIONBONUS_H_

#define EXPLOSION_RANGE 180

#include "Bonus.h"

namespace dxco {

class ExplosionBonus: public Bonus {
public:
	ExplosionBonus(GameModel* model, cocos2d::CCSprite* sprite,
			std::map<int, Animation*>& animations);

	void applyBonus();
};

} /* namespace dxco */

#endif /* EXPLOSIONBONUS_H_ */
