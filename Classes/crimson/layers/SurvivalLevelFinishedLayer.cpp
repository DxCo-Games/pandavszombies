#include "SurvivalLevelFinishedLayer.h"

#include "../../dxco/SpriteUtil.h"
#include "../../dxco/LabelUtil.h"
#include "../../dxco/StringUtil.h"

namespace dxco {

SurvivalLevelFinishedLayer::SurvivalLevelFinishedLayer(float x, float y, float width, float height) : Container(x, y, width, height) {

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	cocos2d::CCSprite* gameOverTitle = SpriteUtil::create("game_over_title.png", visibleSize.width * 0.2, visibleSize.height * 0.7,
														   visibleSize.width * 0.6, visibleSize.height * 0.15);

	this->addChild(gameOverTitle);

	cocos2d::CCSprite* placaGameOver = SpriteUtil::create("placa_game_over.png", visibleSize.width * 0.2, visibleSize.height * 0.3,
														   visibleSize.width * 0.6, visibleSize.height * 0.4);

	this->addChild(placaGameOver);

	cocos2d::CCSprite* menuButtonSprite = SpriteUtil::create("buttons/menu_button.png", visibleSize.width * 0.2, visibleSize.height * 0.15, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);

	SpriteUtil::leftAlign(gameOverTitle, menuButtonSprite);

	this->addChild(menuButtonSprite);

	this->menuButton = new GameTypeSelectionButton(menuButtonSprite);

	cocos2d::CCSprite* tryAgainButtonSprite = SpriteUtil::create("buttons/try_again_button.png", visibleSize.width * 0.2, visibleSize.height * 0.15, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);

	SpriteUtil::rightAlign(gameOverTitle, tryAgainButtonSprite);

	this->addChild(tryAgainButtonSprite);
	this->tryAgainButton = new SurvivalButton(tryAgainButtonSprite);

	this->pointsLabel = dxco::LabelUtil::create(StringUtil::toString(0), 14, visibleSize.width / 2, 10, dxco::LabelUtil::BOTTOM, dxco::LabelUtil::RIGHT, "fonts/KBStickToThePlan.ttf");

	pointsLabel->setPositionX(placaGameOver->getPositionX() - 0.26 * dxco::SpriteUtil::getWidth(placaGameOver));
	pointsLabel->setPositionY(placaGameOver->getPositionY() - 0.20 * dxco::SpriteUtil::getHeight(placaGameOver));
	this->addChild(pointsLabel, 10);

	cocos2d::CCSprite* trophy = SpriteUtil::create("trophy.png", visibleSize.width * 0.2, visibleSize.height * 0.7, dxco::SpriteUtil::getWidth(placaGameOver) * 0.13, dxco::SpriteUtil::getHeight(placaGameOver) * 0.3);
	trophy->setPositionX(pointsLabel->getPositionX() + 0.05 * dxco::SpriteUtil::getWidth(placaGameOver));
	trophy->setPositionY(pointsLabel->getPositionY() + 0.08 * dxco::SpriteUtil::getHeight(placaGameOver));

	this->addChild(trophy, 10);

	this->killsLabel = dxco::LabelUtil::create(StringUtil::toString(0), 14, visibleSize.width / 2, 10, dxco::LabelUtil::BOTTOM, dxco::LabelUtil::RIGHT, "fonts/KBStickToThePlan.ttf");
	killsLabel->setPositionX(trophy->getPositionX() + 0.23 * dxco::SpriteUtil::getWidth(placaGameOver));
	killsLabel->setPositionY(pointsLabel->getPositionY());

	this->addChild(killsLabel, 10);

	cocos2d::CCSprite* cross = SpriteUtil::create("cross.png", visibleSize.width * 0.2, visibleSize.height * 0.7, dxco::SpriteUtil::getWidth(placaGameOver) * 0.13, dxco::SpriteUtil::getHeight(placaGameOver) * 0.3);
	cross->setPositionX(killsLabel->getPositionX() + 0.08 * dxco::SpriteUtil::getWidth(placaGameOver));
	cross->setPositionY(trophy->getPositionY());

	this->addChild(cross, 10);

	this->coinsLabel = dxco::LabelUtil::create(StringUtil::toString(0), 14, visibleSize.width / 2, 10, dxco::LabelUtil::BOTTOM, dxco::LabelUtil::RIGHT, "fonts/KBStickToThePlan.ttf");
	coinsLabel->setPositionX(cross->getPositionX() + 0.17 * dxco::SpriteUtil::getWidth(placaGameOver));
	coinsLabel->setPositionY(pointsLabel->getPositionY());

	this->addChild(coinsLabel, 10);

	cocos2d::CCSprite* coin = SpriteUtil::create("coin.png", visibleSize.width * 0.2, visibleSize.height * 0.7, dxco::SpriteUtil::getWidth(placaGameOver) * 0.13, dxco::SpriteUtil::getHeight(placaGameOver) * 0.3);
	coin->setPositionX(coinsLabel->getPositionX() + 0.08 * dxco::SpriteUtil::getWidth(placaGameOver));
	coin->setPositionY(trophy->getPositionY());

	this->addChild(coin, 10);

	this->setTouchEnabled(false);
	hide();
}

void SurvivalLevelFinishedLayer::show(int points, int kills, int coins) {

	this->killsLabel->setString(StringUtil::intToKString(kills).c_str());
	this->coinsLabel->setString(StringUtil::intToKString(coins).c_str());
	this->pointsLabel->setString(StringUtil::intToKString(points).c_str());

	this->setVisible(true);
	this->setTouchEnabled(true);
}

void SurvivalLevelFinishedLayer::hide() {
	this->setVisible(false);
}

void SurvivalLevelFinishedLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {

	cocos2d::CCTouch* touch = (cocos2d::CCTouch*) (pTouches->anyObject());
	cocos2d::CCPoint location = touch->getLocationInView();
	location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

	this->menuButton->touch(location);
	this->tryAgainButton->touch(location);
}

} /* namespace dxco */
