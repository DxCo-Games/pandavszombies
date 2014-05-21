#include "HelloWorldScene.h"
#include "BonusFactory.h"
#include "GameModel.h"
#include "HealthBonus.h"
#include "WeaponBonus.h"
#include "../dxco/SpriteUtil.h"
#include <cstdlib>

namespace dxco {

BonusFactory::BonusFactory() {
}

void BonusFactory::createBonus(GameModel* model, cocos2d::CCPoint location) {
	if (rand() % 100 < BONUS_PROBABILITY) {
		std::map<int, dxco::Animation*> animations;
		Bonus* bonus;
		switch (rand() % 4) {
			case 0: {	//Health bonus
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("health.png", location.x, location.y, 30, 20);
				bonus = (Bonus*) new HealthBonus(model, bonusSprite, animations);
				break;
			}
			case 1:{ // Shotgun
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("sg.png", location.x, location.y, 50, 20);
				bonus = (Bonus*) new WeaponBonus(model, bonusSprite, animations, Player::SHOTGUN);
				break;
			}
			case 2: {
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("smg.png", location.x, location.y, 40, 30);
				bonus = (Bonus*) new WeaponBonus(model, bonusSprite, animations, Player::SMG_);
				break;
			}
			case 3: {
				cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("p.png", location.x, location.y, 35, 30);
				bonus = (Bonus*) new WeaponBonus(model, bonusSprite, animations, Player::PISTOL);
				break;
			}
		}
		model->bonuses.push_back(bonus);
		model->mapa->addChild(bonus->getSprite());
	}
}

} /* namespace dxco */
