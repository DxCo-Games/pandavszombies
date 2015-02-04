#ifndef BUYPOWERUPBUTTON_H_
#define BUYPOWERUPBUTTON_H_

#include "../../dxco/Button.h"

namespace dxco {

class EquipPandaItem;

class BuyPowerUpButton: public ButtonDxCo {
public:
	BuyPowerUpButton(cocos2d::CCSprite* sprite, EquipPandaItem* item);
	EquipPandaItem *item;

	virtual void execute();
};

} /* namespace dxco */

#endif /* BUYPOWERUPBUTTON_H_ */
