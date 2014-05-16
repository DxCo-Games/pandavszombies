/*
 * BonusFactory.cpp
 *
 *  Created on: May 16, 2014
 *      Author: facundo
 */

#include "BonusFactory.h"
#include <cstdlib>

namespace dxco {

BonusFactory::BonusFactory() {
}

void BonusFactory::createBonus(GameModel* model) {
	if (rand() % 100 < BONUS_PROBABILITY) {
		//create new bonus
		//switch to randomly pick the bonus
	}
}

} /* namespace dxco */
