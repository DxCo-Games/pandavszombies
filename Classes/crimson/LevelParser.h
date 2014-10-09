/*
 * LevelParser.h
 *
 *  Created on: Oct 9, 2014
 *      Author: gsosarolon
 */

#ifndef LEVELPARSER_H_
#define LEVELPARSER_H_

#include <string>
#include <vector>
#include "levels/EnemyWave.h"

namespace dxco {

class LevelParser {
	static std::vector<EnemyWave*> parse(std::string levelPath);
};

} /* namespace dxco */
#endif /* LEVELPARSER_H_ */
