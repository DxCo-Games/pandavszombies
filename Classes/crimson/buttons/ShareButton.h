#ifndef CRIMSON_BUTTONS_SHAREBUTTON_H_
#define CRIMSON_BUTTONS_SHAREBUTTON_H_

#include "../../dxco/Button.h"

namespace dxco {
class GameModel;

class ShareButton: public ButtonDxCo {
public:
	ShareButton(cocos2d::CCSprite* sprite, GameModel* model);
	GameModel* model;
	virtual void execute();

	std::string takeScreenshot();
};

} /* namespace dxco */

#endif /* CRIMSON_BUTTONS_SHAREBUTTON_H_ */
