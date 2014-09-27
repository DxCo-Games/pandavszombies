/*
 * SurvivalLevel.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: facundo
 */

#include "SurvivalLevel.h"

namespace dxco {

SurvivalLevel::SurvivalLevel(GameModel* model): Level(model, *new std::vector<EnemyWave*>) { //apuesto a que esto pincha :P

}

} /* namespace dxco */
