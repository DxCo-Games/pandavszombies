#ifndef SURVIVALLEVELFINISHEDLAYER_H_
#define SURVIVALLEVELFINISHEDLAYER_H_

#include "cocos2d.h"

#include "../buttons/GameTypeSelectionButton.h"
#include "../buttons/SurvivalButton.h"

namespace dxco {

class SurvivalLevelFinishedLayer:  public cocos2d::CCLayer {
public:
	SurvivalLevelFinishedLayer();

	virtual bool init();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(SurvivalLevelFinishedLayer);

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
private:
	GameTypeSelectionButton* menuButton;
	SurvivalButton* tryAgainButton;
};

} /* namespace dxco */

#endif /* SURVIVALLEVELFINISHEDLAYER_H_ */