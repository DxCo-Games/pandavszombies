#ifndef BAZOOKA_H_
#define BAZOOKA_H_

#define BAZOOKA_FREQUENCY 0.5

#include "Weapon.h"

namespace dxco {

class GameModel;

class Bazooka: public Weapon {
public:
	Bazooka(GameModel* model);

	void shoot();

	void createBulletSprite(float x, float y, float angleBullet, float rotation);
};

} /* namespace dxco */
#endif /* BAZOOKA_H_ */
