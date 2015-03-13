#include "Mapa.h"
#include "../dxco/Animation.h"
#include "../dxco/SpriteUtil.h"

namespace dxco {

Mapa::Mapa(float x, float y, float width, float height) : Container(x, y, width, height) {
	cocos2d::CCSprite *obstacleSprite = SpriteUtil::create("cross.png", width/2, height/2, width*0.2, width*0.2);
	std::map<int, Animation*> animations;
	Item* obstacle = new Item(obstacleSprite, animations);
	this->obstacles.push_back(obstacle);
	this->addChild(obstacleSprite);
}

} /* namespace dxco */
