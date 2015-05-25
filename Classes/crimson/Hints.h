#ifndef CRIMSON_HINTS_H_
#define CRIMSON_HINTS_H_

#include <string>

namespace dxco {

class GameModel;

class Hints {
public:
	Hints(GameModel* model);
	GameModel *model;

	/*
	 * To be called at the end of every play.
	 */
	std::string getHint();

	std::string firstPowerup();
	std::string powerup();
	std::string playAnother();
	std::string powerupForSurvival();
	std::string superbossFireball();
	std::string flamethrowerFrenzy();
};

} /* namespace dxco */

#endif /* CRIMSON_HINTS_H_ */
