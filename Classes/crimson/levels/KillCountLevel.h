#ifndef KILLCOUNTLEVEL_H_
#define KILLCOUNTLEVEL_H_

#include "Level.h"

namespace dxco {

//Story mode level that finishes after a fixed amount of enemies have been killed
class KillCountLevel: public Level {
public:
	KillCountLevel(GameModel *model, std::vector<EnemyWave*>& waves, int kills);

	virtual bool isFinished();
	virtual void updateInterface();

	int kills;
};

} /* namespace dxco */

#endif /* KILLCOUNTLEVEL_H_ */
