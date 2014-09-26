#include "HelloWorldScene.h"
#include "BonusFactory.h"
#include "../GameModel.h"
#include "HealthBonus.h"
#include "WeaponBonus.h"
#include "PuntosBonus.h"
#include "ExplosionBonus.h"
#include "WeaponSpeedBonus.h"
#include "ShieldBonus.h"
#include "FreezeBombBonus.h"
#include "MovementSpeedBonus.h"
#include "../../dxco/SpriteUtil.h"
#include <cstdlib>

namespace dxco {

BonusFactory::BonusFactory() {
}

void BonusFactory::createBonus(GameModel* model, cocos2d::CCPoint location) {
	if (rand() % 100 < BONUS_PROBABILITY) {
		std::map<int, dxco::Animation*> animations;
		Bonus* bonus;

		switch (rand() % 12) {
			case 0: {	//Health bonus
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/health.png", location.x, location.y, 45, 45);
				bonus = new HealthBonus(model, bonusSprite, animations);
				break;
			}
			case 1:{ // Shotgun
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/shotgun.png", location.x, location.y, 45, 45);
				bonus = new WeaponBonus(model, bonusSprite, animations, Player::SHOTGUN);
				break;
			}
			case 2: {
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/smg.png", location.x, location.y, 45, 45);
				bonus = new WeaponBonus(model, bonusSprite, animations, Player::SMG_);
				break;
			}
			case 3: {
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/flame_thrower.png", location.x, location.y, 45, 45);
				bonus = new WeaponBonus(model, bonusSprite, animations, Player::FIRE);
				break;
			}
			case 4: {
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/bomb.png", location.x, location.y, 45, 45);
				bonus = new ExplosionBonus(model, bonusSprite, animations);
				break;
			}
			case 5: {
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/speed.png", location.x, location.y, 45, 45);
				bonus = new MovementSpeedBonus(model, bonusSprite, animations);
				break;
			}
			case 6: {
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/bonus_points.png", location.x, location.y, 45, 45);
				bonus = new PuntosBonus(model, bonusSprite, animations);
				break;
			}
			case 7: {
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/weapon_speed.png", location.x, location.y, 45, 45);
				bonus = new WeaponSpeedBonus(model, bonusSprite, animations);
				break;
			}
			case 8: {
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/shield.png", location.x, location.y, 45, 45);
				bonus = new ShieldBonus(model, bonusSprite, animations);
				break;
			}
			case 9: {
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/bazooka.png", location.x, location.y, 45, 45);
				bonus = new WeaponBonus(model, bonusSprite, animations, Player::BAZOOKA);
				break;
			}
			case 10: {
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/freeze.png", location.x, location.y, 45, 45);
				bonus = new FreezeBombBonus(model, bonusSprite, animations);
				break;
			}
			case 11: {
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/fire.png", location.x, location.y, 45, 45);
				bonus = new WeaponBonus(model, bonusSprite, animations, Player::FIREBULLET);
				break;
			}
		}

		model->bonuses.push_back(bonus);
		model->mapa->putInside(bonus); //make sure it's reachable in the map
		model->mapa->addChild(bonus->getSprite());
	}
}

} /* namespace dxco */
