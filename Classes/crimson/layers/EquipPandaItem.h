#ifndef EQUIPPANDAITEM_H_
#define EQUIPPANDAITEM_H_

#include "../../dxco/Container.h"
#include <string>

namespace dxco {

class EquipPandaItem : public Container, public Touchable {
public:
	EquipPandaItem(std::string item, float x, float y, float width, float height);
	std::string item;
	int price;

	void execute();

private:
	std::string getImagePath();
	std::string getExplicacion();
	std::string getName();
	std::string getBuyImagePath();
	std::string _getPrice();
};

} /* namespace dxco */
#endif /* EQUIPPANDAITEM_H_ */
