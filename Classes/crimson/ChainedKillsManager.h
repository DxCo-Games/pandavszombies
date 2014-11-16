#ifndef CHAINEDKILLSMANAGER_H_
#define CHAINEDKILLSMANAGER_H_

#define CHAIN_DURATION 0.75
#define CHAIN_SCORE_PER_KILL 40

#include "cocos2d.h"

namespace dxco {

class GameModel;

class ChainedKillsManager: public cocos2d::CCObject {
public:
	ChainedKillsManager(GameModel *model);

	void addKill();
	void updateView();
	void setChainMessage();
	void restart();

	bool shouldUpdateLabel();

	void updatePlayerScore();

	GameModel *model;
	int currentChainLength;
	float lastKillTime;
	int lastChainLength;
};

} /* namespace dxco */

#endif /* CHAINEDKILLSMANAGER_H_ */
