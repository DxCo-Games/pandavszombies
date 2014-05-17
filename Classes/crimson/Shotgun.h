#ifndef SHOTGUN_H_
#define SHOTGUN_H_

#include "Weapon.h"

namespace dxco {

class Shotgun: public Weapon {
public:
	Shotgun(GameModel* model);
	void shoot();
};

} /* namespace dxco */

#endif /* SHOTGUN_H_ */
