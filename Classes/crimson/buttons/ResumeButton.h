#ifndef RESUMEBUTTON_H_
#define RESUMEBUTTON_H_

#include "../../dxco/Button.h"

namespace dxco {

class GameModel;

class ResumeButton: public dxco::ButtonDxCo {
public:
	ResumeButton(GameModel* model, cocos2d::CCNode* sprite);

	void execute();
private:
	GameModel* model;
};

} /* namespace dxco */

#endif /* RESUMEBUTTON_H_ */
