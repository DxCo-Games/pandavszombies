#include "BombBonusFactory.h"
#include "ExplosionBonus.h"
#include "../GameModel.h"
#include "../GameProperties.h"
#include "../../dxco/SpriteUtil.h"

namespace dxco {

BombBonusFactory::BombBonusFactory(): BonusFactory() {
	// TODO Auto-generated constructor stub
}

void BombBonusFactory::createBonus(GameModel* model, cocos2d::CCPoint location) {
	if (rand() % 100 < model->prop->get("bonus.probability")) {
		cocos2d::CCSprite* bonusSprite = dxco::SpriteUtil::create("bonus/bomb.png", location.x, location.y, 45, 45);
		std::map<int, dxco::Animation*> animations;
		Bonus* bonus = new ExplosionBonus(model, bonusSprite, animations);
		this->addToMap(model, bonus);
	}
}

} /* namespace dxco */
