#include "FireWeapon.h"
#include "../dxco/SpriteUtil.h"

namespace dxco {

FireWeapon::FireWeapon(GameModel* model, float x, float y) :
		Container(x, y, 0, 0) {
	this->model = model;

	cocos2d::CCTexture2D* texture = dxco::SpriteUtil::createTexture("fire.png");
	fire = cocos2d::CCParticleSystemQuad::create("fire.plist");

	fire->setPosition(0, 0);
	fire->setTexture(texture);

	this->addChild(fire);
}

void FireWeapon::setRotation(float rotation) {

	float R = 40;
	float angle = -rotation / 57.2957795;
	cocos2d::CCSize visibleSize =
					cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	fire->setPosition(visibleSize.width/2 + 40 + R * cos(angle), visibleSize.height/2 + 40 + R * sin(angle));
}


} /* namespace dxco */
