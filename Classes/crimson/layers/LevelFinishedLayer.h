#ifndef SURVIVALLEVELFINISHEDLAYER_H_
#define SURVIVALLEVELFINISHEDLAYER_H_

#include "cocos2d.h"

#include "../../dxco/Container.h"

#include "../buttons/GameTypeSelectionButton.h"
#include "../buttons/RestartSurvivalButton.h"
#include "../buttons/NextLevelButton.h"
#include "../buttons/EquipPandaButton.h"
#include "../buttons/ShareButton.h"

#define LEVEL_COUNT 100

namespace dxco {

class GameModel;
class LevelFinishedLayer:  public Container {
public:
	LevelFinishedLayer(GameModel* model, float x, float y, float width, float height, bool survival, int level = 0);

	void show();
	void hide();

	void prepareShare();
	void returnShare();

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void enableTouch();

	cocos2d::CCLabelTTF* killsLabel;
	cocos2d::CCLabelTTF* pointsLabel;
	cocos2d::CCLabelTTF* coinsLabel;
private:

	bool survival;

	GameModel *model;
	GameTypeSelectionButton* menuButton;
	ShareButton* shareButton;
	RestartSurvivalButton* tryAgainButton;
	NextLevelButton* nextLevelButton;
	EquipPandaButton* equipPandaButton;
	cocos2d::CCSprite* title;
	cocos2d::CCSprite* starsSprite;
};

} /* namespace dxco */

#endif /* SURVIVALLEVELFINISHEDLAYER_H_ */
