#ifndef RANKINGLAYER_H_
#define RANKINGLAYER_H_

#include "AbstractMenuLayer.h"

namespace dxco {

class RankingLayer : public AbstractMenuLayer {
public:
	virtual bool init();
	static cocos2d::CCScene* scene();

	CREATE_FUNC(RankingLayer);

	void ccTouchesBegan(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
	void ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
};

} /* namespace dxco */

#endif /* RANKINGLAYER_H_ */
