#ifndef TOPDOWNITEM_H_
#define TOPDOWNITEM_H_

#include "../dxco/Item.h"

namespace dxco {

class TopDownItem: public Item {
public:

	/* Construct a top down item with <anglePositions> amount of different
	 * rotation animations. If it has 2 different states (i.e. standing and walking)
	 * and 8 rotation positions then animations 0-7 will be the standing animation in
	 * each rotation and 8-15 will be the walking animations in each rotation.
	 * */
	TopDownItem(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations,
			int anglePositions = 8);

	int anglePositions;
	int state;
	float rotation;

	/* Return the state i.e. animation number to match the current rotation and
	 * item state.
	 * */
	int getState();

	//from 0 to anglePositions - 1 based on current rotation
	int getAngleState();
	float getRotation();
	void setRotation(float rotation);
};

} /* namespace dxco */

#endif /* TOPDOWNITEM_H_ */
