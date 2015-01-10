#include "AbstractMenuLayer.h"

namespace dxco {

AbstractMenuLayer::AbstractMenuLayer()  {
	this->setKeypadEnabled(true);
}

void AbstractMenuLayer::keyBackClicked() {
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->popScene();
}

} /* namespace dxco */
