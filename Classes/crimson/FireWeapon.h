#ifndef FIREWEAPON_H_
#define FIREWEAPON_H_

#include "Weapon.h"

namespace dxco {

class FireWeapon: public Weapon {
public:
	FireWeapon(GameModel* model);
	void shoot();
};

} /* namespace dxco */

#endif /* FIREWEAPON_H_ */
