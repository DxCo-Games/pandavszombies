#ifndef MENUPARALLAXITEM_H_
#define MENUPARALLAXITEM_H_

#include "cocos2d.h"
#include "Container.h"

namespace dxco {

class MenuParallaxItem : public Container, public Touchable {
public:
	MenuParallaxItem(float x, float y, float width, float height);
	virtual ~MenuParallaxItem();
	virtual void execute() = 0;

	void move(float x, float y);
	void moveX(float x);
	void moveY(float y);
};

} /* namespace dxco */
#endif /* MENUPARALLAXITEM_H_ */
