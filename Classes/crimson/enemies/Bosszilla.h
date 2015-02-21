/*
 * Bosszilla.h
 *
 *  Created on: Feb 21, 2015
 *      Author: facundo
 */

#ifndef BOSSZILLA_H_
#define BOSSZILLA_H_

#include "Boss.h"

namespace dxco {

class Bosszilla: public dxco::Boss {
public:
	Bosszilla(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int level, std::string type);

	virtual float getColitionRatio();
};

} /* namespace dxco */

#endif /* BOSSZILLA_H_ */
