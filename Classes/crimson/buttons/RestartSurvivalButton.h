#ifndef RESTARTSURVIVALBUTTON_H_
#define RESTARTSURVIVALBUTTON_H_

#include "../../dxco/Button.h"

namespace dxco {

class GameModel;

class RestartSurvivalButton : public dxco::ButtonDxCo {
public:
	RestartSurvivalButton(GameModel* model, cocos2d::CCNode* sprite);

	void execute();
private:
	GameModel* model;
};

} /* namespace dxco */
#endif /* RESTARTSURVIVALBUTTON_H_ */
