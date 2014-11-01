#include "LevelFinishedLayer.h"

#include "../../dxco/SpriteUtil.h"
#include "../../dxco/LabelUtil.h"
#include "../../dxco/StringUtil.h"

namespace dxco {

LevelFinishedLayer::LevelFinishedLayer(float x, float y, float width, float height, bool survival, int level) : Container(x, y, width, height) {

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	cocos2d::CCSprite* title = NULL;

	if (survival) {
		title = SpriteUtil::create("game_over_title.png", visibleSize.width * 0.2, visibleSize.height * 0.7,
														  visibleSize.width * 0.6, visibleSize.height * 0.15);
	} else {
		title = SpriteUtil::create("level_finished_title.png", visibleSize.width * 0.15, visibleSize.height * 0.7,
															   visibleSize.width * 0.7, visibleSize.height * 0.15);
	}

	this->addChild(title);

	if (!survival) {
		cocos2d::CCSprite* stars = SpriteUtil::create("buttons/LEVELS-x" + StringUtil::toString(3) + ".png", visibleSize.width * 0.15, visibleSize.height * 0.3, visibleSize.height * 0.4 * 0.45, visibleSize.height * 0.4);
		this->addChild(stars);
	}

	cocos2d::CCSprite* placaGameOver = SpriteUtil::create("placa_game_over.png", visibleSize.width * (survival ? 0.20 : 0.25), visibleSize.height * 0.3,
														   visibleSize.width * 0.6, visibleSize.height * 0.4);

	this->addChild(placaGameOver);

	cocos2d::CCSprite* menuButtonSprite = SpriteUtil::create("buttons/menu_button.png", visibleSize.width * 0.2, visibleSize.height * 0.15, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);

	SpriteUtil::leftAlign(title, menuButtonSprite);

	this->addChild(menuButtonSprite);

	if (!survival && level != LEVEL_COUNT) {
		cocos2d::CCSprite* nextLevelSprite = SpriteUtil::create("buttons/next_button.png", visibleSize.width * 0.65, visibleSize.height * 0.15, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);
		this->addChild(nextLevelSprite);

		SpriteUtil::copyScale(menuButtonSprite, nextLevelSprite);

		this->nextLevelButton = new NextLevelButton(nextLevelSprite, level + 1);
	}

	this->menuButton = new GameTypeSelectionButton(menuButtonSprite);

	cocos2d::CCSprite* tryAgainButtonSprite = SpriteUtil::create("buttons/try_again_button.png", visibleSize.width * 0.2, visibleSize.height * 0.15, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);

	SpriteUtil::rightAlign(title, tryAgainButtonSprite);

	this->addChild(tryAgainButtonSprite);
	this->tryAgainButton = new SurvivalButton(tryAgainButtonSprite);

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

	this->setVisible(true);
	this->setTouchEnabled(true);
}

void LevelFinishedLayer::hide() {
	this->setVisible(false);
}

void LevelFinishedLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {

	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
	cocos2d::CCPoint location = touch->getLocationInView();
	location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

	this->menuButton->touch(location);
	this->tryAgainButton->touch(location);

	if (this->nextLevelButton != NULL) {
		this->nextLevelButton->touch(location);
	}
}

} /* namespace dxco */