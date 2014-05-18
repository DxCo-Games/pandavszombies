#ifndef FIREWEAPON_H_
#define FIREWEAPON_H_

#include "cocos2d.h"
#include "../dxco/Container.h"

namespace dxco {

class GameModel;
class FireWeapon : public Container {
public:
	FireWeapon(GameModel* model, float x, float y);

	GameModel* model;
	void setRotation(float rotation);
	cocos2d::CCParticleSystem* fire;
};

} /* namespace dxco */
#endif /* FIREWEAPON_H_ */
