#ifndef FIREWEAPON_H_
#define FIREWEAPON_H_

#include "Weapon.h"

#define FIRE_DAMAGE 8

namespace dxco {

class FireWeapon: public Weapon {
public:
	FireWeapon(GameModel* model);
	void update(float dt);
	void shoot();
};

} /* namespace dxco */

#endif /* FIREWEAPON_H_ */
