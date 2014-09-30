#ifndef GAMETYPESELECTIONLAYER_H_
#define GAMETYPESELECTIONLAYER_H_

#include "cocos2d.h"

namespace dxco {

class GameTypeSelectionLayer :  public cocos2d::CCLayer {
public:
	GameTypeSelectionLayer();

	virtual bool init();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(GameTypeSelectionLayer);
};

} /* namespace dxco */

#endif /* GAMETYPESELECTIONLAYER_H_ */
