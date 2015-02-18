#ifndef SUPERBOSS_H_
#define SUPERBOSS_H_

#include "Boss.h"

namespace dxco {

class SuperBoss: public Boss {
public:
	SuperBoss(GameModel* model, cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations, int level, std::string type, int extraType);
	virtual float getColitionRatio();
};

} /* namespace dxco */

#endif /* SUPERBOSS_H_ */
