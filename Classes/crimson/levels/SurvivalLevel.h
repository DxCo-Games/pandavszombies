#ifndef SURVIVALLEVEL_H_
#define SURVIVALLEVEL_H_

#define SURVIVAL_ENEMY_DT 0.3
#define SURVIVAL_BOSS_DT 15
#define SURVIVAL_SPEED_DT 30

#include "Level.h"

namespace dxco {

class SurvivalLevel: public Level {
public:
	SurvivalLevel(GameModel* model);

	virtual bool isFinished();
	virtual void update(float dt);
	virtual void restartLevel();

	float enemyDt;
	float bossDt;
	float speedDt;
};

} /* namespace dxco */

#endif /* SURVIVALLEVEL_H_ */
