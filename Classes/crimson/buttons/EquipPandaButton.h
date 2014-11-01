#ifndef EQUIPPANDABUTTON_H_
#define EQUIPPANDABUTTON_H_

#include "../../dxco/Button.h"

namespace dxco {

class EquipPandaButton : public ButtonDxCo {
public:
	EquipPandaButton(cocos2d::CCSprite* sprite);

	virtual void execute();
};

} /* namespace dxco */

#endif /* SURVIVALBUTTON_H_ */
