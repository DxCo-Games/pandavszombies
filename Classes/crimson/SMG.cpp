/*
 * SMG.cpp
 *
 *  Created on: May 16, 2014
 *      Author: facundo
 */

#include "SMG.h"

namespace dxco {

SMG::SMG(GameModel* model): Weapon(model) {
	this->bulletFrequency = 0.1;
}

} /* namespace dxco */
