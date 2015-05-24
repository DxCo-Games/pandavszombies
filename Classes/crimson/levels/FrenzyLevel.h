#ifndef FRENZYLEVEL_H_
#define FRENZYLEVEL_H_

#include "SurvivalLevel.h"

namespace dxco {
class GameModel;

class FrenzyLevel: public SurvivalLevel {
public:
	FrenzyLevel(GameModel* model);
	virtual std::string getLevelText();
};

} /* namespace dxco */

#endif /* FRENZYLEVEL_H_ */
