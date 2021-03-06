#ifndef SURVIVALLEVEL_H_
#define SURVIVALLEVEL_H_

#define SURVIVAL_ENEMY_LEVEL_DT_BEFORE_50 2.5
#define SURVIVAL_ENEMY_LEVEL_DT_AFTER_50 1.5

#include "Level.h"

namespace dxco {

class SurvivalLevel: public Level {
public:
	SurvivalLevel(GameModel* model, float maxEnemyDt=0.3, float maxBossDt=15);

	virtual bool isFinished();
	virtual void update(float dt);
	virtual void restartLevel();

	virtual std::string getLevelText();

	virtual void updateInterface();
	virtual void showMessage();

	float enemyDt;
	float bossDt;
	float enemyLevelDt;

	float maxEnemyDt;
	float maxBossDt;
	bool showAdd();
};

} /* namespace dxco */

#endif /* SURVIVALLEVEL_H_ */
