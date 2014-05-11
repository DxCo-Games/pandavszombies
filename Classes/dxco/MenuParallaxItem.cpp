#include "MenuParallaxItem.h"
#include "SpriteUtil.h"

namespace dxco {

MenuParallaxItem::MenuParallaxItem(float x, float y, float width, float height) : Container (x, y, width, height), Touchable(this) {

}

MenuParallaxItem::~MenuParallaxItem() {

}


void MenuParallaxItem::move(float x, float y) {
	Container::move(x, y);
}

void MenuParallaxItem::moveX(float x) {
	this->move(x, 0);
}

void MenuParallaxItem::moveY(float y) {
	this->move(0, y);
}

} /* namespace dxco */
