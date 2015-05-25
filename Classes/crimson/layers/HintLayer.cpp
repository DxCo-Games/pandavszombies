#include "HintLayer.h"
#include "../Hints.h"
#include "../GameModel.h"
#include "../../HelloWorldScene.h"
#include "../../dxco/SpriteUtil.h"


namespace dxco {

HintLayer::HintLayer(GameModel *model, float x, float y, float width, float height): Container(x,y,width,height) {
	this->hints = new Hints(model);
	this->model = model;

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	cocos2d::CCSprite* placa = SpriteUtil::create("gameplay/PLACA_texto.png", 0, 0, model->vista->bonus1);
	placa->setScale(1.5);
	placa->setPositionX(visibleSize.width/2);
	placa->setPositionY(visibleSize.height * 0.65);
	this->addChild(placa);

	this->panelText = cocos2d::CCLabelTTF::create("", "fonts/KBStickToThePlan.ttf", 15, cocos2d::CCSize(220,0), cocos2d::kCCTextAlignmentCenter);
	this->panelText->setColor(cocos2d::ccc3(255, 255, 255));
	this->panelText->setPositionX(placa->getPositionX());
	this->panelText->setPositionY(placa->getPositionY());
	this->addChild(this->panelText);

	cocos2d::CCSprite* button = SpriteUtil::create("buttons/BTN_CHLL_OK.png", 0, 0, placa);
	button->setPositionX(placa->getPositionX());
	button->setPositionY(placa->getPositionY() - SpriteUtil::getHeight(placa)/2 - SpriteUtil::getHeight(button)*0.6);
	this->addChild(button);

	this->setVisible(false);
}

void HintLayer::show() {
	std::string hint = this->hints->getHint();
	if (hint != "") {
		this->panelText->setString(hint.c_str());
		this->setVisible(true);
		this->setTouchEnabled(true);
	} else {
		model->vista->levelFinishedLayer->show();
	}
}
void HintLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
	this->setVisible(false);
	this->setTouchEnabled(false);
	model->vista->levelFinishedLayer->show();
}


} /* namespace dxco */
