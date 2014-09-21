#ifndef WEAPONBONUS_H_
#define WEAPONBONUS_H_

#include "Bonus.h"
#include "../Player.h"

namespace dxco {

class WeaponBonus: public Bonus {
public:
	WeaponBonus(GameModel* model, cocos2d::CCSprite* sprite,
			std::map<int, Animation*>& animations, Player::weapons type);

	void applyBonus();
	Player::weapons type;
};

} /* namespace dxco */

#endif /* WEAPONBONUS_H_ */
