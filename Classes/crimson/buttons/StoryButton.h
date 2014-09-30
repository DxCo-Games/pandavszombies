#ifndef STORYBUTTON_H_
#define STORYBUTTON_H_

#include "../../dxco/Button.h"

namespace dxco {

class StoryButton : public ButtonDxCo {
public:
	StoryButton(cocos2d::CCSprite* sprite);

	virtual void execute();
};

} /* namespace dxco */

#endif /* STORYBUTTON_H_ */
