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
#include "EnemyWave.h"
#include "../../dxco/JsonParser.h"
#include "../../dxco/rapidjson/document.h"
#include "cocos2d.h"

namespace dxco {

class GameModel;

class LevelParser {
public:
	static std::vector<EnemyWave*> parse(GameModel* model, std::string levelPath);
};

} /* namespace dxco */
#endif /* LEVELPARSER_H_ */
