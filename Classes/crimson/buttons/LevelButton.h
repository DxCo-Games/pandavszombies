#ifndef LEVELBUTTON_H_
#define LEVELBUTTON_H_

#include "../../dxco/Button.h"

namespace dxco {

class LevelButton: public ButtonDxCo {
public:
	LevelButton(int number, float x, float y);

	void execute();

	int number;
	bool enabled;
	cocos2d::CCLabelTTF* label;
};

} /* namespace dxco */

#endif /* LEVELBUTTON_H_ */
