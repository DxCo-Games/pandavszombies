#ifndef BUTTON_DXCO_H_
#define BUTTON_DXCO_H_

#include "cocos2d.h"
#include "Touchable.h"

namespace dxco {

class ButtonDxCo : public Touchable {
public:
	ButtonDxCo(cocos2d::CCNode* sprite);
	virtual ~ButtonDxCo();

	virtual void execute() = 0;
};

} /* namespace dxco */
#endif /* BUTTON_H_ */
