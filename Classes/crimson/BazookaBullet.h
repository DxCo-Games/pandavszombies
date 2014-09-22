#ifndef BAZOOKABULLET_H_
#define BAZOOKABULLET_H_

#include "Bullet.h"

namespace dxco {

class GameModel;

class BazookaBullet: public dxco::Bullet {
public:
	GameModel* model;
	BazookaBullet(GameModel* model, cocos2d::CCSprite* sprite, float angle, std::map<int, Animation*>& animations);

	void update(float dt);
	void use();
};

} /* namespace dxco */
#endif /* BAZOOKABULLET_H_ */
