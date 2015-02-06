#ifndef SURVIVALBUTTON_H_
#define SURVIVALBUTTON_H_

#include "../../dxco/Button.h"

namespace dxco {

class SurvivalButton : public ButtonDxCo {
public:
	SurvivalButton(cocos2d::CCSprite* sprite, bool frenzy=false);
	bool frenzy;

	virtual void execute();
};

} /* namespace dxco */

#endif /* SURVIVALBUTTON_H_ */
