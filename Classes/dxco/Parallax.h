#ifndef PARALLAX_H_
#define PARALLAX_H_

#include <vector>
#include <string>
#include "cocos2d.h"
#include "ParallaxLayer.h"

namespace dxco {

class Parallax {
public:
	Parallax();
	virtual ~Parallax();

	void addLayer(cocos2d::CCLayer* cclayer, ParallaxLayer* layer);
	void move(float deltaX, float deltaY);
	void restart();
private:
	std::vector<ParallaxLayer*> layers;
};

} /* namespace dxco */
#endif /* PARALLAX_H_ */
