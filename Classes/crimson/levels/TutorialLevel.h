#ifndef TUTORIALLEVEL_H_
#define TUTORIALLEVEL_H_

#include "Level.h"

namespace dxco {

class TutorialLevel: public Level {
public:
	TutorialLevel(GameModel* model);
	virtual bool isFinished();
	virtual void update(float dt);
	virtual void restartLevel();

	virtual void showMessage();

	int currentStep; // 0-3
	float rotationDt;
	float movementDt;
	bool messageDisplayed;
};

} /* namespace dxco */

#endif /* TUTORIALLEVEL_H_ */
