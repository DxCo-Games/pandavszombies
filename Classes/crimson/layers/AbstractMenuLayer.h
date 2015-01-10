#ifndef ABSTRACTMENULAYER_H_
#define ABSTRACTMENULAYER_H_

#include "cocos2d.h"

namespace dxco {

class AbstractMenuLayer : public cocos2d::CCLayer {
public:
	AbstractMenuLayer();

	void keyBackClicked();
};

} /* namespace dxco */

#endif /* ABSTRACTMENULAYER_H_ */
