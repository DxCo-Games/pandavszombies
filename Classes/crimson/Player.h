#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_LIFE 100
#define PLAYER_SPEED 75
#define PLAYER_ANGLE_POSITIONS 16

#include "TopDownItem.h"

namespace dxco {

class GameModel;
class Weapon;

class Player : public TopDownItem {
public:
	Player(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);
	void disparar();

	GameModel* model;
	enum estados { QUIETO, CAMINANDO, HERIDO };
	enum weapons { PISTOL, SHOTGUN, SMG_, MACHINE_GUN, FIRE};
	Weapon* weapon;
	weapons weaponType;

	void setWeapon(weapons type);

	void hurt(float damage); //works with negative too
	bool isActive();

	void update(float dt);
	float life;
	int score;

	bool moving;

	/* Since the player can move and look in different directions
	 * we use a specific angle to track movement direction.
	 * */
	float moveRotation;

};

} /* namespace dxco */
#endif /* PLAYER_H_ */
