#ifndef BOMBA_H_
#define BOMBA_H_

#include "cocos2d.h"

namespace dxco {

class GameModel;

class Bomba {
public:
	Bomba(GameModel* model);
	void explode(float radio);
	GameModel* model;
};

} /* namespace dxco */
#endif /* BOMBA_H_ */
