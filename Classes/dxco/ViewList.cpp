#include "ViewList.h"

namespace dxco {

ViewList::ViewList(float x, float y, float width, float height) : Container(x, y, width, height) {
	this->elementsHeight = 0;
	this->distance = 0;
	this->yMoved = 0;

	cocos2d::CCSize visibleSize =
				cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	this->visibleHeight = visibleSize.height;
	this->loaded = false;
}

void ViewList::addElement(ViewListElement* element) {

	if (element) {
		element->move(0, this->getHeight() - this->elementsHeight - element->getHeight());

		this->elementsHeight += element->getHeight() + this->distance;
		this->elements.push_back(element);
		this->addChild(element);
	}
}

int ViewList::getSize() {
	return this->elements.size();
}
void ViewList::move(float deltaY) {

	if (elements.size()) {
		float move = deltaY;

		if (yMoved + deltaY < 0) {
			move = 0;
		} else if (yMoved + deltaY > (this->elementsHeight - (this->visibleHeight / 2))) {
			move = 0;
		}

		yMoved += move;

		for (int i = 0; i < this->elements.size(); i++) {
			ViewListElement* element = this->elements[i];
			element->move(0, move);
		}
	}
}

void ViewList::setDistance(float distance) {
	this->distance = distance;
}

bool ViewList::isLoaded() {
	return this->loaded;
}

bool ViewList::setLoaded(bool loaded) {
	this->loaded = loaded;
}

} /* namespace dxco */
