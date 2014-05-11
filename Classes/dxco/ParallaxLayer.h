#ifndef PARALLAXLAYER_H_
#define PARALLAXLAYER_H_

#include <string>
#include "cocos2d.h"
#include <vector>

namespace dxco {

class ParallaxLayer {
	friend class Parallax;
public:
	ParallaxLayer(std::string texture, float distance, int yPosition, bool repeat, int width, int height);
	virtual ~ParallaxLayer();

	void move(float deltaX, float deltaY);
	void restart();
protected:
	float distance;
	bool repeat;
	int width;
	int yPosition;
	int height;
	std::vector<cocos2d::CCSprite*> sprites;
	float getOffset(cocos2d::CCSprite* sprite);
	cocos2d::CCSprite* getLastSprite();

};

} /* namespace dxco */
#endif /* PARALLAXLAYER_H_ */
