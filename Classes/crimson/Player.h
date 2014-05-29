#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_LIFE 100
#define PLAYER_SPEED 80

#include "../dxco/Item.h"

namespace dxco {

class GameModel;
class Weapon;

class Player : public Item {
public:
	Player(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);
	void disparar();

	GameModel* model;
	Weapon* weapon;
	enum estados { CAMINANDO, QUIETO };
	enum weapons { PISTOL, SHOTGUN, SMG_, MACHINE_GUN, FIRE};

	void setWeapon(weapons type);

	int getState();
	void hurt(float damage); //works with negative too
	bool isActive();

	void update(float dt);
	int state;
	float life;

	float angle;
	bool moving;
	float width;
	float height;

	cocos2d::CCPoint getLocation();
};

} /* namespace dxco */
#endif /* PLAYER_H_ */
