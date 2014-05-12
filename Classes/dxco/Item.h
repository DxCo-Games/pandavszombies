#ifndef ITEM_H_
#define ITEM_H_

#include "cocos2d.h"
#include "Animation.h"

#include <vector>

namespace dxco {

class Item {
public:
	Item(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations);

	virtual void update(float dt);
	virtual void updatePosition(float speed, float dt);

	virtual int getState();
	virtual cocos2d::CCPoint getLocation();

	virtual float getHeight();
	virtual float getWidth();
	virtual float getX();
	virtual float getY();
	virtual float getTopPosition();
	virtual float getBottomPosition();
	virtual float getRightPosition();
	virtual float getLeftPosition();

	virtual void move(float deltaX, float deltaY);
	virtual void moveTo(float x, float y);
	virtual void restartPosition();
	virtual cocos2d::CCSprite* getSprite();

	virtual void goTo(cocos2d::CCPoint point, float distance);
protected:
	cocos2d::CCSprite* sprite;
	cocos2d::CCTexture2D* defaultTexture;

	std::map<int, Animation*> animations;

	float xInitial;
	float yInitial;
	int state;
};

} /* namespace dxco */
#endif /* ITEM_H_ */
