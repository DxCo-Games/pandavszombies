#ifndef GAMETYPESELECTIONBUTTON_H_
#define GAMETYPESELECTIONBUTTON_H_

#include "../../dxco/Button.h"

namespace dxco {

class GameTypeSelectionButton: public dxco::ButtonDxCo {
public:
	GameTypeSelectionButton(cocos2d::CCSprite* sprite);

	virtual void execute();
};

} /* namespace dxco */

#endif /* GAMETYPESELECTIONBUTTON_H_ */
