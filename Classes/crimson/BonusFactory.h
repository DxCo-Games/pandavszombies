/*
 * BonusFactory.h
 *
 *  Created on: May 16, 2014
 *      Author: facundo
 */

#ifndef BONUSFACTORY_H_
#define BONUSFACTORY_H_

#define BONUS_PROBABILITY 20

namespace dxco {

class GameModel;

class BonusFactory {
public:
	BonusFactory();

	void createBonus(GameModel* model);
};

} /* namespace dxco */

#endif /* BONUSFACTORY_H_ */
