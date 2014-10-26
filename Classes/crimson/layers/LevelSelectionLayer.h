#ifndef LEVELSELECTIONLAYER_H_
#define LEVELSELECTIONLAYER_H_

#include "cocos2d.h"
#include <vector>

namespace dxco {

class LevelButton;
class LevelScreenButton;

class LevelSelectionLayer: public cocos2d::CCLayer {
public:
	LevelSelectionLayer();

	virtual bool init();

	static cocos2d::CCScene* scene(int page=0);

	CREATE_FUNC(LevelSelectionLayer);

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	std::vector<LevelButton*> buttons;
	int page;
	LevelScreenButton *prev;
	LevelScreenButton *next;
};

} /* namespace dxco */

#endif /* LEVELSELECTIONLAYER_H_ */
