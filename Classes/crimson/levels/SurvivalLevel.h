#ifndef SURVIVALLEVEL_H_
#define SURVIVALLEVEL_H_

#define SURVIVAL_ENEMY_LEVEL_DT 60

#include "Level.h"

namespace dxco {

class SurvivalLevel: public Level {
public:
	SurvivalLevel(GameModel* model, float maxEnemyDt=0.3, float maxBossDt=15);

	virtual bool isFinished();
	virtual void update(float dt);
	virtual void restartLevel();

	virtual void updateInterface();

	float enemyDt;
	float bossDt;
	float enemyLevelDt;

	float maxEnemyDt;
	float maxBossDt;
};

} /* namespace dxco */

#endif /* SURVIVALLEVEL_H_ */
