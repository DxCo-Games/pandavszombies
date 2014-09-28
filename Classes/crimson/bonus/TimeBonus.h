#ifndef TIMEBONUS_H_
#define TIMEBONUS_H_

#include "Bonus.h"

#include "../GameModel.h"

namespace dxco {

class TimeBonus : public Bonus {
public:
	TimeBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, float bonusDuration);

	virtual void update(float dt);
	float dtBonusAcquired;
	float bonusDuration;
	bool bonusAcquired;
};

} /* namespace dxco */

#endif /* TIMEBONUS_H_ */
