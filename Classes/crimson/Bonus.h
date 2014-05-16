#ifndef BONUS_H_
#define BONUS_H_

#include "dxco/Item.h"

namespace dxco {

class GameModel;

class Bonus: public Item {
public:
	Bonus(GameModel* model, cocos2d::CCSprite* sprite,
			std::map<int, Animation*>& animations);

	void update(float dt);
	virtual void applyBonus() = 0;

	GameModel* model;
};

} /* namespace dxco */

#endif /* BONUS_H_ */
