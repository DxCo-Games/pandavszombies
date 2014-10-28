#ifndef NEXTLEVELBUTTON_H_
#define NEXTLEVELBUTTON_H_

#include "../../dxco/Button.h"

namespace dxco {

class NextLevelButton : public ButtonDxCo {
public:
	NextLevelButton(cocos2d::CCSprite* sprite, int levelNumber);

	virtual void execute();
private:
	int levelNumber;
};

} /* namespace dxco */

#endif /* NEXTLEVELBUTTON_H_ */
