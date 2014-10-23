#ifndef SURVIVALLEVELFINISHEDLAYER_H_
#define SURVIVALLEVELFINISHEDLAYER_H_

#include "cocos2d.h"

#include "../../dxco/Container.h"

#include "../buttons/GameTypeSelectionButton.h"
#include "../buttons/SurvivalButton.h"

namespace dxco {

class SurvivalLevelFinishedLayer:  public Container {
public:
	SurvivalLevelFinishedLayer(float x, float y, float width, float height);

	void show(int points, int kills, int coins);
	void hide();

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	cocos2d::CCLabelTTF* killsLabel;
	cocos2d::CCLabelTTF* pointsLabel;
	cocos2d::CCLabelTTF* coinsLabel;
private:
	GameTypeSelectionButton* menuButton;
	SurvivalButton* tryAgainButton;
};

} /* namespace dxco */

#endif /* SURVIVALLEVELFINISHEDLAYER_H_ */
