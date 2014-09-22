#ifndef FIREBULLETWEAPON_H_
#define FIREBULLETWEAPON_H_

#include "Weapon.h"

namespace dxco {

class FireBulletWeapon: public Weapon {
public:
	FireBulletWeapon(GameModel* model);
	virtual void createBulletSprite(float x, float y, float angleBullet, float rotation);
};

} /* namespace dxco */

#endif /* FIREBULLETWEAPON_H_ */
