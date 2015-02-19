#ifndef STORYBUTTON_H_
#define STORYBUTTON_H_

#include "../../dxco/Button.h"

namespace dxco {

class StoryButton : public ButtonDxCo {
public:
	StoryButton(cocos2d::CCSprite* sprite, int currentPage);

	virtual void execute();
private:
	int currentPage;
};

} /* namespace dxco */

#endif /* STORYBUTTON_H_ */
