#ifndef PAUSELAYER_H_
#define PAUSELAYER_H_

#include "cocos2d.h"

#include "../../dxco/Container.h"

#include "../buttons/GameTypeSelectionButton.h"
#include "../buttons/RestartSurvivalButton.h"
#include "../buttons/ResumeButton.h"

namespace dxco {

class PauseLayer :  public Container {
public:
	PauseLayer(GameModel* model, float x, float y, float width, float height, cocos2d::CCSprite* scaleMaster);

	void show();
	void hide();

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
private:
	GameTypeSelectionButton* menuButton;
	RestartSurvivalButton* tryAgainButton;
	ResumeButton* resumeButton;
};

} /* namespace dxco */

#endif /* PAUSELAYER_H_ */
