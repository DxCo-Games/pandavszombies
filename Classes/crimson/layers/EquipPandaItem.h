#ifndef EQUIPPANDAITEM_H_
#define EQUIPPANDAITEM_H_

#include "../../dxco/Container.h"
#include <string>
#include <vector>

namespace dxco {

class BuyPowerUpButton;

class EquipPandaItem : public Container {
public:
	EquipPandaItem(std::string item, float x, float y, float width, float height,
			cocos2d::CCSprite* scaleMaster);
	std::string item;
	int price;

	BuyPowerUpButton *button;
	void applyPowerUp();

	static std::vector<std::string> getMejoras();
	float getMaxX();
private:
	bool isActivo();
	int getCantidadDisponible();
	std::string getImagePath();
	std::string getName();
	std::string getDetail();
	std::string getBuyImagePath();
	int getPrice();
};

} /* namespace dxco */
#endif /* EQUIPPANDAITEM_H_ */
