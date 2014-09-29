#ifndef WEAPONBONUS_H_
#define WEAPONBONUS_H_

#include "TimeBonus.h"
#include "../Player.h"

#define WEAPON_BONUS_DURATION 15

namespace dxco {

class WeaponBonus: public TimeBonus {
public:
	WeaponBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, Player::weapons type);

	virtual void update(float dt);
	void applyBonus();
	void removeBonus();

	Player::weapons type;
};

} /* namespace dxco */

#endif /* WEAPONBONUS_H_ */
