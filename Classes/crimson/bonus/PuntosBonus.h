#ifndef PUNTOSBONUS_H_
#define PUNTOSBONUS_H_

#include "Bonus.h"
#include "../GameModel.h"

#define CANTIDAD_PUNTOS 1000

namespace dxco {

class PuntosBonus : public Bonus {
public:
	PuntosBonus(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);

	void applyBonus();
};

} /* namespace dxco */

#endif /* PUNTOSBONUS_H_ */
