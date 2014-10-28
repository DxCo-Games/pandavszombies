#ifndef LEVELPARSER_H_
#define LEVELPARSER_H_

#include <string>
#include "Level.h"
#include "../../dxco/JsonParser.h"
#include "../../dxco/rapidjson/document.h"
#include "cocos2d.h"

namespace dxco {

class GameModel;

class LevelParser {
public:
	static Level* parse(GameModel* model, std::string levelPath);
};

} /* namespace dxco */
#endif /* LEVELPARSER_H_ */
