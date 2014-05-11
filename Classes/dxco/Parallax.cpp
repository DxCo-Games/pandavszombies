#include "Parallax.h"

namespace dxco {

Parallax::Parallax() {

}

void Parallax::addLayer(cocos2d::CCLayer* cclayer, ParallaxLayer* layer) {
	this->layers.push_back(layer);

	for (int i = 0; i < layer->sprites.size(); i++) {
		cclayer->addChild(layer->sprites[i]);
	}
}

void Parallax::move(float deltaX, float deltaY) {

	for (int i = 0; i < this->layers.size(); i++) {
		ParallaxLayer* layer = this->layers[i];
		layer->move(deltaX, deltaY);
	}
}

void Parallax::restart() {
	for (int i = 0; i < this->layers.size(); i++) {
		ParallaxLayer* layer = this->layers[i];
		layer->restart();
	}
}

Parallax::~Parallax() {

}

} /* namespace dxco */
