#ifndef LEVELSELECTIONLAYER_H_
#define LEVELSELECTIONLAYER_H_

#include "cocos2d.h"

#include "AbstractMenuLayer.h"

#include <vector>
#define CLICK_MAX_DELTA 4

namespace dxco {

class LevelButton;
class LevelScreenButton;

class LevelSelectionLayer: public AbstractMenuLayer {
public:
	LevelSelectionLayer();

	virtual bool init();

	static cocos2d::CCScene* scene(int page=0);

	CREATE_FUNC(LevelSelectionLayer);

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	std::vector<LevelButton*> buttons;
	int page;
	int touchId;
	LevelScreenButton *prev;
	LevelScreenButton *next;

	cocos2d::CCPoint beginLocation;
	cocos2d::CCPoint lastLocation;

	float minX;
	float maxX;

};

} /* namespace dxco */

#endif /* LEVELSELECTIONLAYER_H_ */
