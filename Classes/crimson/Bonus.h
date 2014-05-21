#ifndef BONUS_H_
#define BONUS_H_

#define WEAPON_DT 30

#include "dxco/Item.h"

namespace dxco {

class GameModel;

class Bonus: public Item {
public:
	Bonus(GameModel* model, cocos2d::CCSprite* sprite,
			std::map<int, Animation*>& animations);

	void update(float dt);
	virtual void applyBonus() = 0;
	void removeBonus();

	GameModel* model;
	float dt;
};

} /* namespace dxco */

#endif /* BONUS_H_ */
