#ifndef GAMETYPESELECTIONLAYER_H_
#define GAMETYPESELECTIONLAYER_H_

#include "cocos2d.h"

#include "../buttons/SurvivalButton.h"
#include "../buttons/StoryButton.h"

namespace dxco {

class GameTypeSelectionLayer :  public cocos2d::CCLayer {
public:
	GameTypeSelectionLayer();

	virtual bool init();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(GameTypeSelectionLayer);

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
private:
	SurvivalButton* survivalButton;
	StoryButton* storyButton;
};

} /* namespace dxco */

#endif /* GAMETYPESELECTIONLAYER_H_ */
