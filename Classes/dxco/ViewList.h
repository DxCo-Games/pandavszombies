#ifndef VIEWLIST_H_
#define VIEWLIST_H_

#include "Container.h"
#include "ViewListElement.h"
#include <vector>

namespace dxco {

class ViewList : public Container {
public:
	ViewList(float x, float y, float width, float height);

	void addElement(ViewListElement* element);
	void move(float deltaY);
	void setDistance(float distance);
	bool isLoaded();
	bool setLoaded(bool loaded);
	int getSize();
private:
	std::vector<ViewListElement*> elements;
	float elementsHeight;
	float distance;
	float yMoved;
	float visibleHeight;
	bool loaded;
};

} /* namespace dxco */
#endif /* VIEWLIST_H_ */
