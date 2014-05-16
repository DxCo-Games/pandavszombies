#include "HelloWorldScene.h"
#include "BonusFactory.h"
#include "GameModel.h"
#include "HealthBonus.h"
#include "../dxco/SpriteUtil.h"
#include <cstdlib>

namespace dxco {

BonusFactory::BonusFactory() {
}

void BonusFactory::createBonus(GameModel* model, cocos2d::CCPoint location) {
	if (rand() % 100 < BONUS_PROBABILITY) {
		//create new bonus
		cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("health.png", location.x, location.y, 15, 15);
		std::map<int, dxco::Animation*> animations;
		Bonus* bonus = (Bonus*) new HealthBonus(model, bonusSprite, animations);
		model->bonuses.push_back(bonus);
		model->vista->addChild(bonus->getSprite());
	}
}

} /* namespace dxco */
