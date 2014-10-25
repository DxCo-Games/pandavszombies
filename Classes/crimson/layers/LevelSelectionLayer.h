#ifndef LEVELSELECTIONLAYER_H_
#define LEVELSELECTIONLAYER_H_

#include "cocos2d.h"
#include <vector>

namespace dxco {

class LevelButton;

class LevelSelectionLayer: public cocos2d::CCLayer {
public:
	LevelSelectionLayer();

	virtual bool init();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(LevelSelectionLayer);

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	std::vector<LevelButton*> buttons;
};

} /* namespace dxco */

#endif /* LEVELSELECTIONLAYER_H_ */
