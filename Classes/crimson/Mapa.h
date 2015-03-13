#ifndef MAPA_H_
#define MAPA_H_

#include "../dxco/Container.h"
#include "../dxco/Item.h"
#include <vector>

namespace dxco {

class Mapa : public Container {
public:
	Mapa(float x, float y, float width, float height);

	std::vector<Item*> obstacles;
};

} /* namespace dxco */
#endif /* MAPA_H_ */
