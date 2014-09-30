#include "ChainedKillsManager.h"
#include "GameModel.h"
#include "../dxco/StringUtil.h"
#include "../HelloWorldScene.h"


namespace dxco {

ChainedKillsManager::ChainedKillsManager(GameModel *model): cocos2d::CCObject() {
	this->model = model;
	this->currentChainLength = 0;
	this->lastChainLength = 0;
	this->lastKillTime = -10;
}

void ChainedKillsManager::addKill() {
	//update kills counters
	if (this->model->timer - this->lastKillTime < CHAIN_DURATION) {
		this->currentChainLength +=1;
	} else {
		this->currentChainLength = 1;
	}
	this->lastKillTime = this->model->timer;
}


void ChainedKillsManager::updateView() {
	cocos2d::CCLabelTTF *label = this->model->vista->killsChainLabel;
	if (this->shouldUpdateLabel()) {
		std::string playerKillsText = StringUtil::toString(this->currentChainLength) + " Kills";
		label->setString(playerKillsText.c_str());
		label->setPositionX(this->model->vista->timerLabel->getPositionX());
		this->lastChainLength = this->currentChainLength;
		cocos2d::CCSequence *seq = cocos2d::CCSequence::create(cocos2d::CCDelayTime::create(1), cocos2d::CCFadeOut::create(0.15),
				cocos2d::CCCallFuncN::create(this, cocos2d::SEL_CallFuncN(&ChainedKillsManager::setChainMessage)),
				cocos2d::CCFadeIn::create(0.15), cocos2d::CCDelayTime::create(1), cocos2d::CCFadeOut::create(0.3),
				NULL);

		if (label->getOpacity() == 0 && label->numberOfRunningActions() == 0) {
			label->runAction(cocos2d::CCSequence::create(cocos2d::CCFadeIn::create(0.3), seq, NULL));
		} else if (label->getOpacity() == 255) {
			label->stopAllActions();
			label->runAction(seq);
		}
	}
}

bool ChainedKillsManager::shouldUpdateLabel() {
	//at least 3 chained kills, chain time not finished
	//or a greater chain is still being shown
	return (this->currentChainLength > 4
			&& this->model->timer - this->lastKillTime < CHAIN_DURATION
			&& this->currentChainLength > this->lastChainLength);
}

void ChainedKillsManager::setChainMessage(){
	int kills = this->lastChainLength;
	this->lastChainLength = 0;
	cocos2d::CCLabelTTF *label = this->model->vista->killsChainLabel;
	if (kills < 15) {
		label->setString("Good");
	} else if (kills < 30) {
		label->setString("Excellent");
	} else if (kills < 50) {
		label->setString("Outstanding");
	} else {
		label->setString("Toasty!");
	}
	label->setPositionX(this->model->vista->timerLabel->getPositionX());
}

void ChainedKillsManager::restart() {
	this->currentChainLength = 0;
	this->lastKillTime = -10;
}

} /* namespace dxco */
