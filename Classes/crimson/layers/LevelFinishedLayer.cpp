#include "LevelFinishedLayer.h"

#include "../../dxco/SpriteUtil.h"
#include "../../dxco/LabelUtil.h"
#include "../../dxco/StringUtil.h"

namespace dxco {

LevelFinishedLayer::LevelFinishedLayer(GameModel* model, float x, float y, float width, float height, bool survival, int level) : Container(x, y, width, height) {

	this->survival = survival;

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	if (survival) {
		this->title = SpriteUtil::create("game_over_title.png", visibleSize.width * 0.2, visibleSize.height * 0.7,
														  visibleSize.width * 0.6, visibleSize.height * 0.15);
	} else {
		this->title = SpriteUtil::create("level_finished_title.png", visibleSize.width * 0.15, visibleSize.height * 0.7,
															   visibleSize.width * 0.7, visibleSize.height * 0.15);
	}

	this->addChild(this->title);

	cocos2d::CCSprite* placaGameOver = SpriteUtil::create("placa_game_over.png", visibleSize.width * (survival ? 0.20 : 0.25), visibleSize.height * 0.3,
														   visibleSize.width * 0.6, visibleSize.height * 0.4);

	this->addChild(placaGameOver);

	cocos2d::CCSprite* menuButtonSprite = SpriteUtil::create("buttons/menu_button.png", visibleSize.width * 0.2, visibleSize.height * 0.15, title);
	SpriteUtil::leftAlign(this->title, menuButtonSprite);

	this->addChild(menuButtonSprite);

	if (!survival && level != LEVEL_COUNT) {
		cocos2d::CCSprite* nextLevelSprite = SpriteUtil::create("buttons/next_button.png", visibleSize.width * 0.65, visibleSize.height * 0.15, menuButtonSprite);
		this->addChild(nextLevelSprite);
		this->nextLevelButton = new NextLevelButton(nextLevelSprite, level + 1);
	} else {
		this->nextLevelButton = NULL;
	}

	this->menuButton = new GameTypeSelectionButton(menuButtonSprite);

	cocos2d::CCSprite* tryAgainButtonSprite = NULL;

	if (survival) {
		tryAgainButtonSprite = SpriteUtil::create("buttons/try_again_button.png", visibleSize.width * 0.6, visibleSize.height * 0.15, title);
	} else {
		tryAgainButtonSprite = SpriteUtil::create("buttons/try_again_button.png", visibleSize.width * 0.55, visibleSize.height * 0.15, title);
	}

	this->addChild(tryAgainButtonSprite);
	this->tryAgainButton = new RestartSurvivalButton(model, tryAgainButtonSprite);

	cocos2d::CCSprite* equipPandaButtonSprite = SpriteUtil::create("buttons/equip_panda_button.png", visibleSize.width * 0.2, visibleSize.height * 0.15, title);
	SpriteUtil::rightAlign(this->title, equipPandaButtonSprite);

	this->addChild(equipPandaButtonSprite);
	this->equipPandaButton = new EquipPandaButton(equipPandaButtonSprite);

	this->pointsLabel = cocos2d::CCLabelTTF::create("0", "fonts/KBStickToThePlan.ttf", 14);
	pointsLabel->setAnchorPoint(ccp(1,0.5f));

	pointsLabel->setPositionX(placaGameOver->getPositionX() - 0.26 * dxco::SpriteUtil::getWidth(placaGameOver));
	pointsLabel->setPositionY(placaGameOver->getPositionY() - 0.1 * dxco::SpriteUtil::getHeight(placaGameOver));
	this->addChild(pointsLabel, 10);

	cocos2d::CCSprite* trophy = SpriteUtil::create("trophy.png", visibleSize.width * 0.2, visibleSize.height * 0.7, dxco::SpriteUtil::getWidth(placaGameOver) * 0.13, dxco::SpriteUtil::getHeight(placaGameOver) * 0.3);
	trophy->setPositionX(pointsLabel->getPositionX() + 0.05 * dxco::SpriteUtil::getWidth(placaGameOver));
	trophy->setPositionY(pointsLabel->getPositionY());

	this->addChild(trophy, 10);

	this->killsLabel = cocos2d::CCLabelTTF::create("0", "fonts/KBStickToThePlan.ttf", 14);
	killsLabel->setAnchorPoint(ccp(1,0.5f));

	killsLabel->setPositionX(trophy->getPositionX() + 0.23 * dxco::SpriteUtil::getWidth(placaGameOver));
	killsLabel->setPositionY(pointsLabel->getPositionY());

	this->addChild(killsLabel, 10);

	cocos2d::CCSprite* cross = SpriteUtil::create("cross.png", visibleSize.width * 0.2, visibleSize.height * 0.7, dxco::SpriteUtil::getWidth(placaGameOver) * 0.13, dxco::SpriteUtil::getHeight(placaGameOver) * 0.3);
	cross->setPositionX(killsLabel->getPositionX() + 0.05 * dxco::SpriteUtil::getWidth(placaGameOver));
	cross->setPositionY(trophy->getPositionY());

	this->addChild(cross, 10);

	this->coinsLabel = cocos2d::CCLabelTTF::create("0", "fonts/KBStickToThePlan.ttf", 14);
	coinsLabel->setAnchorPoint(ccp(1,0.5f));

	coinsLabel->setPositionX(cross->getPositionX() + 0.20 * dxco::SpriteUtil::getWidth(placaGameOver));
	coinsLabel->setPositionY(pointsLabel->getPositionY());

	this->addChild(coinsLabel, 10);

	cocos2d::CCSprite* coin = SpriteUtil::create("coin.png", visibleSize.width * 0.2, visibleSize.height * 0.7, dxco::SpriteUtil::getWidth(placaGameOver) * 0.13, dxco::SpriteUtil::getHeight(placaGameOver) * 0.3);
	coin->setPositionX(coinsLabel->getPositionX() + 0.05 * dxco::SpriteUtil::getWidth(placaGameOver));
	coin->setPositionY(trophy->getPositionY());

	this->addChild(coin, 10);

	this->setTouchEnabled(false);
	hide();
}

void LevelFinishedLayer::show(int points, int kills, int coins, int stars) {

	this->killsLabel->setString(StringUtil::intToKString(kills).c_str());
	this->coinsLabel->setString(StringUtil::intToKString(coins).c_str());
	this->pointsLabel->setString(StringUtil::intToKString(points).c_str());

	if (!this->survival) {

		if (stars == 0) {

			cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
			this->title = SpriteUtil::create("game_over_title.png", visibleSize.width * 0.15, visibleSize.height * 0.7, visibleSize.width * 0.7, visibleSize.height * 0.15);

			this->addChild(title);

			this->nextLevelButton->sprite->setVisible(false);
			this->tryAgainButton->sprite->setPositionX(visibleSize.width * 0.68);
		}

		cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
		cocos2d::CCSprite* starsSprite = SpriteUtil::create("buttons/LEVEL-FIN-SLOTS-" + StringUtil::toString(stars) + ".png", visibleSize.width * 0.15, visibleSize.height * 0.3, visibleSize.height * 0.4 * 0.45, visibleSize.height * 0.4);
		this->addChild(starsSprite);
	}

	this->setVisible(true);
	this->setTouchEnabled(true);
}

void LevelFinishedLayer::hide() {
	this->setTouchEnabled(false);
	this->setVisible(false);
}

void LevelFinishedLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {

	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
	cocos2d::CCPoint location = touch->getLocationInView();
	location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);


	if (this->nextLevelButton != NULL) {
		this->nextLevelButton->touch(location);
	}

	this->menuButton->touch(location);
	this->tryAgainButton->touch(location);
	this->equipPandaButton->touch(location);
}

} /* namespace dxco */
