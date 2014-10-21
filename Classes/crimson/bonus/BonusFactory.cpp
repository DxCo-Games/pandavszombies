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
		Bonus* bonus;

		int weaponProbability = 20;
		if (model->player->weaponType == Player::PISTOL) {
			weaponProbability = 80;
		}

		if (rand() % 100 < weaponProbability) {
			bonus = this->createWeaponBonus(model, location);
		} else {
			std::map<int, dxco::Animation*> animations;

			switch (rand() % 7) {
				case 0: {	//Health bonus
					cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/health.png", location.x, location.y, 45, 45);
					bonus = new HealthBonus(model, bonusSprite, animations);
					break;
				}
				case 1: {
					cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/bomb.png", location.x, location.y, 45, 45);
					bonus = new ExplosionBonus(model, bonusSprite, animations);
					break;
				}
				case 2: {
					cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/speed.png", location.x, location.y, 45, 45);
					bonus = new MovementSpeedBonus(model, bonusSprite, animations);
					break;
				}
				case 3: {
					cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/bonus_points.png", location.x, location.y, 45, 45);
					bonus = new PuntosBonus(model, bonusSprite, animations);
					break;
				}
				case 4: {
					cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/weapon_speed.png", location.x, location.y, 45, 45);
					bonus = new WeaponSpeedBonus(model, bonusSprite, animations);
					break;
				}
				case 5: {
					cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/shield.png", location.x, location.y, 45, 45);
					bonus = new ShieldBonus(model, bonusSprite, animations);
					break;
				}
				case 6: {
					cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/freeze.png", location.x, location.y, 45, 45);
					bonus = new FreezeBombBonus(model, bonusSprite, animations);
					break;
				}
			}
		}

		model->bonuses.push_back(bonus);
		model->mapa->putInside(bonus); //make sure it's reachable in the map
		model->mapa->addChild(bonus->getSprite());
	}
}

Bonus* BonusFactory::createWeaponBonus(GameModel* model, cocos2d::CCPoint location) {
	std::map<int, dxco::Animation*> animations;
	switch (rand() % 5) {
	case 0: {
		cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/shotgun.png", location.x, location.y, 45, 45);
		return new WeaponBonus(model, bonusSprite, animations, Player::SHOTGUN);
	}
	case 1: {
		cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/smg.png", location.x, location.y, 45, 45);
		return new WeaponBonus(model, bonusSprite, animations, Player::SMG_);
	}
	case 2: {
		cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/flame_thrower.png", location.x, location.y, 45, 45);
		return new WeaponBonus(model, bonusSprite, animations, Player::FIRE);
	}
	case 3: {
		cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/bazooka.png", location.x, location.y, 45, 45);
		return new WeaponBonus(model, bonusSprite, animations, Player::BAZOOKA);
	}
	case 4: {
		cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/fire.png", location.x, location.y, 45, 45);
		return new WeaponBonus(model, bonusSprite, animations, Player::FIREBULLET);
	}
	}

}

} /* namespace dxco */
