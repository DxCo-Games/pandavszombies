#include "FireBulletWeapon.h"
#include "GameModel.h"
#include "Bullet.h"
#include "../dxco/SpriteUtil.h"

namespace dxco {

FireBulletWeapon::FireBulletWeapon(GameModel* model): Weapon(model) {
	this->bullets = 50;
	this->bulletFrequency = 0.4;
}

void FireBulletWeapon::createBulletSprite(float xBulletPosition, float yBulletPosition, float angleBullet, float rotation) {
	//need to tweak the coordinates as the location of the panda is not exactly its center.
	cocos2d::CCSprite* spriteBullet = SpriteUtil::create("bullet.png", xBulletPosition - 2.5 - 20, yBulletPosition - 2.5 - 20, 5, 5);

	/** degrees to radians */
	float radianAngle = (angleBullet + rotation) / -57.2957795;

	std::map<int, Animation*> animations;
	Bullet* bullet = new Bullet(spriteBullet, radianAngle, animations);
	bullet->persistent = true;


	cocos2d::CCParticleSystemQuad* firecomet = cocos2d::CCParticleSystemQuad::create("firebullet.plist");
	firecomet->setPositionType(cocos2d::kCCPositionTypeRelative);
	firecomet->setRotation(180);
	spriteBullet->addChild(firecomet);
	spriteBullet->setRotation(angleBullet + rotation);
	spriteBullet->setOpacity(0);
	this->model->addBullet(bullet);
}

} /* namespace dxco */
