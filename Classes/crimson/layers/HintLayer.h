#ifndef CRIMSON_LAYERS_HINTLAYER_H_
#define CRIMSON_LAYERS_HINTLAYER_H_

#include "../../dxco/Container.h"

namespace dxco {

class GameModel;
class Hints;

class HintLayer: public Container {
public:
	HintLayer(GameModel *model, float x, float y, float width, float height);

	void show();
	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	Hints *hints;
	GameModel *model;
	cocos2d::CCLabelTTF* panelText;
};

} /* namespace dxco */

#endif /* CRIMSON_LAYERS_HINTLAYER_H_ */
