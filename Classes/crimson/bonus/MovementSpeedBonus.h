#ifndef MOVEMENTSPEEDBONUS_H_
#define MOVEMENTSPEEDBONUS_H_

#define MOVEMENT_BONUS_RATE 1.40
#define MOVEMENT_SPEED_BONUS_DURATION 10

#include "Bonus.h"

namespace dxco {

class MovementSpeedBonus: public Bonus {
public:
	MovementSpeedBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);

	void applyBonus();

	void removeBonus();

	void update(float dt);
private:

	float dtBonusAcquired;
	bool bonusAcquired;

	void removeSprite();
};

} /* namespace dxco */

#endif /* MOVEMENTSPEEDBONUS_H_ */
