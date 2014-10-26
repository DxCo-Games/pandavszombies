#ifndef LEVELSCREENBUTTON_H_
#define LEVELSCREENBUTTON_H_

#include "../../dxco/Button.h"
#include "cocos2d.h"

namespace dxco {

class LevelScreenButton: public ButtonDxCo {
public:
	LevelScreenButton(cocos2d::CCSprite* sprite, int page);

	void execute();
	int page;
};

} /* namespace dxco */

#endif /* LEVELSCREENBUTTON_H_ */
