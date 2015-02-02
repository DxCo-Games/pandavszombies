#ifndef EQUIPPANDALAYER_H_
#define EQUIPPANDALAYER_H_

#include "../../dxco/Container.h"

#include "cocos2d.h"
#include "EquipPandaItem.h"
#include "AbstractMenuLayer.h"

#include <string>
#include <vector>
#define CLICK_MAX_DELTA 4

namespace dxco {

class EquipPandaLayer : public AbstractMenuLayer {
public:

	virtual bool init();
	static cocos2d::CCScene* scene();

	CREATE_FUNC(EquipPandaLayer);


	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint beginLocation;
	cocos2d::CCPoint lastLocation;
	bool movingRigthAnimation;
	bool movingLeftAnimation;
	float moved;

	std::vector<EquipPandaItem*> items;

	int getTotalCoins();

	void addSkills(float skillsPandaX, float skillsPandaY, float skillsPandaWidth, float skillsPandaHeight);
	void addSkill(float skillsPandaX, float skillsPandaY, float skillsPandaWidth, float skillsPandaHeight, std::string skillName, int skillValue, int index);
	int getLife();
	int getSpeed();
	int getAttack();
	int getWeaponTime();
	int getBonus();
	void loadMejoras(float skillsPandaWidth, float skillsPandaHeight, float skillsPandaX, float skillsPandaY);

	int touchId;
};

} /* namespace dxco */

#endif /* GAMETYPESELECTIONLAYER_H_ */
