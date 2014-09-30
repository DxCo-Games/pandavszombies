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
	if (this->model->timer - this->lastKillTime < 1) {
		this->currentChainLength +=1;
	} else {
		this->currentChainLength = 1;
	}
	this->lastKillTime = this->model->timer;
}


//TODO add update and move timer
//TODO 1 should be a constant here
//TODO not that much logic in update view
void ChainedKillsManager::updateView() {
	cocos2d::CCLabelTTF *label = this->model->vista->killsChainLabel;
	if (this->currentChainLength > 2 && this->model->timer - this->lastKillTime < 1) {
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

void ChainedKillsManager::setChainMessage(){
	int kills = this->lastChainLength;
	cocos2d::CCLabelTTF *label = this->model->vista->killsChainLabel;
	if (kills < 10) {
		label->setString("Good");
	} else if (kills < 20) {
		label->setString("Excellent");
	} else if (kills < 30) {
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
