#ifndef TIMEDLEVEL_H_
#define TIMEDLEVEL_H_

#include "Level.h"

namespace dxco {

//A story mode level that finishes after a fixed amount of seconds
class TimedLevel: public Level {
public:
	TimedLevel(GameModel *model, std::vector<EnemyWave*>& waves, int seconds, std::string title="");

	virtual bool isFinished();
	virtual void update(float dt);
	virtual void updateFreezed(float dt);
	virtual void restartLevel();
	virtual void updateInterface();

	virtual void showMessage();

	float dt;
	int seconds;
};

} /* namespace dxco */

#endif /* TIMEDLEVEL_H_ */
