/*
 * RestartSurvivalButton.h
 *
 *  Created on: Nov 3, 2014
 *      Author: gsosarolon
 */

#ifndef RESTARTSURVIVALBUTTON_H_
#define RESTARTSURVIVALBUTTON_H_

#include "../../dxco/Button.h"

namespace dxco {

class GameModel;

class RestartSurvivalButton : public ButtonDxCo {
public:
	RestartSurvivalButton(GameModel* model, cocos2d::CCNode* sprite);

	void execute();
	GameModel* model;
};

} /* namespace dxco */
#endif /* RESTARTSURVIVALBUTTON_H_ */
