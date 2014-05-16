#ifndef WEAPON_H_
#define WEAPON_H_

namespace dxco {

class GameModel;

class Weapon {
public:
	Weapon(GameModel* model);

	void update(float dt);

	virtual void shoot();

	GameModel* model;
	float bulletDt;
	float bulletFrequency;
};


} /* namespace dxco */

#endif /* WEAPON_H_ */
