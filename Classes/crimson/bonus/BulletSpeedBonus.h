#ifndef BULLETSPEEDBONUS_H_
#define BULLETSPEEDBONUS_H_

#include "TimeBonus.h"

#define BULLET_BONUS_RATE 2.0
#define BULLET_SPEED_BONUS_DURATION 10

namespace dxco {

class BulletSpeedBonus: public TimeBonus {
public:
	BulletSpeedBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);

	void applyBonus();

	void removeBonus();
};

} /* namespace dxco */

#endif /* BULLETSPEEDBONUS_H_ */
