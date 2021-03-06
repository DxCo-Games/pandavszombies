#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_ANGLE_POSITIONS 16
#define PLAYER_UP_DELTA 20

#include "../dxco/TopDownItem.h"

namespace dxco {

class GameModel;
class Weapon;
class WeaponBonus;

class Player : public TopDownItem {
public:
	Player(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);
	void disparar();

	GameModel* model;
	enum estados { QUIETO, CAMINANDO, CAMINANDO_INVERTIDO, HERIDO };
	enum weapons { PISTOL, SHOTGUN, SMG_, MACHINE_GUN, FIRE, BAZOOKA, FIREBULLET};
	Weapon* weapon;
	weapons weaponType;

	void setWeapon(weapons type);

	void hurt(float damage); //works with negative too
	bool isActive();

	void update(float dt);
	float life;
	int score;
	float movementSpeedBonus;
	float weaponSpeedBonus;
	int shieldActivated;
	WeaponBonus* weaponBonus;

	bool moving;
	bool rotating;
	bool invertido;

	/* Since the player can move and look in different directions
	 * we use a specific angle to track movement direction.
	 * */
	float moveRotation;

	void updateFireLocation();

};

} /* namespace dxco */
#endif /* PLAYER_H_ */
