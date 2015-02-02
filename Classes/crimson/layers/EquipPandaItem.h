#ifndef EQUIPPANDAITEM_H_
#define EQUIPPANDAITEM_H_

#include "../../dxco/Container.h"
#include <string>
#include <vector>

namespace dxco {

class EquipPandaItem : public Container, public Touchable {
public:
	EquipPandaItem(std::string item, float x, float y, float width, float height);
	std::string item;
	int price;

	void execute();

	static std::vector<std::string> getMejoras();
private:
	bool isActivo();
	int getCantidadDisponible();
	std::string getImagePath();
	std::string getExplicacion();
	std::string getName();
	std::string getBuyImagePath();
	int getPrice();
};

} /* namespace dxco */
#endif /* EQUIPPANDAITEM_H_ */
