#ifndef GAMETYPESELECTIONLAYER_H_
#define GAMETYPESELECTIONLAYER_H_

#include "cocos2d.h"

#include "../buttons/SurvivalButton.h"
#include "../buttons/StoryButton.h"
#include "../buttons/EquipPandaButton.h"
#include "AbstractMenuLayer.h"

namespace dxco {

class GameTypeSelectionLayer : public AbstractMenuLayer {
public:
	GameTypeSelectionLayer();

	virtual bool init();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(GameTypeSelectionLayer);

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
private:
	SurvivalButton* survivalButton;
	SurvivalButton* frenzyButton;
	StoryButton* storyButton;
	EquipPandaButton* equipPandaButton;
};

} /* namespace dxco */

#endif /* GAMETYPESELECTIONLAYER_H_ */
