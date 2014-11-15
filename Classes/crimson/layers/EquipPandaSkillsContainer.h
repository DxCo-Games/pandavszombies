/*
 * EquipPandaSkillsContainer.h
 *
 *  Created on: Nov 5, 2014
 *      Author: gsosarolon
 */

#ifndef EQUIPPANDASKILLSCONTAINER_H_
#define EQUIPPANDASKILLSCONTAINER_H_

#include "cocos2d.h"
#include "../../dxco/Container.h"
#include <string>

namespace dxco {

class EquipPandaSkillsContainer : public Container {
public:
	EquipPandaSkillsContainer(float x, float y, float width, float height);

	void addSkill(std::string name, int value);
};

} /* namespace dxco */
#endif /* EQUIPPANDASKILLSCONTAINER_H_ */
