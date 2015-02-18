#ifndef BONUS_H_
#define BONUS_H_

#define BONUS_DT 30.0

#include "dxco/Item.h"

namespace dxco {

class GameModel;

class Bonus: public Item {
public:
	Bonus(GameModel* model, cocos2d::CCSprite* sprite,
			std::map<int, Animation*>& animations);

	virtual void update(float dt);
	virtual void applyBonus() = 0;
	virtual void removeBonus();

	GameModel* model;
	float dt;
	std::string sound;
};

} /* namespace dxco */

#endif /* BONUS_H_ */
