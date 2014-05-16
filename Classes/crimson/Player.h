#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_LIFE 100

#include "../dxco/Item.h"

namespace dxco {

class GameModel;

class Player : public Item {
public:
	Player(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);
	void disparar();

	GameModel* model;
	enum estados { CAMINANDO, QUIETO };

	int getState();
	void hurt(float damage); //works with negative too
	bool isActive();

	int state;
	float life;
};

} /* namespace dxco */
#endif /* PLAYER_H_ */
