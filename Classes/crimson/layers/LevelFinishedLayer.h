#ifndef SURVIVALLEVELFINISHEDLAYER_H_
#define SURVIVALLEVELFINISHEDLAYER_H_

#include "cocos2d.h"

#include "../../dxco/Container.h"

#include "../buttons/GameTypeSelectionButton.h"
#include "../buttons/SurvivalButton.h"
#include "../buttons/NextLevelButton.h"

#define LEVEL_COUNT 99

namespace dxco {

class LevelFinishedLayer:  public Container {
public:
	LevelFinishedLayer(float x, float y, float width, float height, bool survival, int level = 0);

	void show(int points, int kills, int coins, int stars);
	void hide();

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	cocos2d::CCLabelTTF* killsLabel;
	cocos2d::CCLabelTTF* pointsLabel;
	cocos2d::CCLabelTTF* coinsLabel;
private:
	GameTypeSelectionButton* menuButton;
	SurvivalButton* tryAgainButton;
	NextLevelButton* nextLevelButton;
};

} /* namespace dxco */

#endif /* SURVIVALLEVELFINISHEDLAYER_H_ */