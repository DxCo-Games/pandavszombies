/*
 * EquipPandaSkillsContainer.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: gsosarolon
 */

#include "EquipPandaSkillsContainer.h"
#include "cocos2d.h"
#include "../../dxco/SpriteUtil.h"

namespace dxco {


EquipPandaSkillsContainer::EquipPandaSkillsContainer(float x, float y, float width, float height): Container(x, y, width, height) {

	cocos2d::CCSprite* skillsPanda = SpriteUtil::create("equip/MEJORA_panda.png", 0, 0, width, height);
	this->addChild(skillsPanda);
}

void EquipPandaSkillsContainer::addSkill(std::string name, int value) {

}

} /* namespace dxco */
