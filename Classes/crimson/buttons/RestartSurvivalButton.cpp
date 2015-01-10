#include "RestartSurvivalButton.h"

#include "../GameModel.h"
#include "../../HelloWorldScene.h"

namespace dxco {

RestartSurvivalButton::RestartSurvivalButton(GameModel* model, cocos2d::CCNode* sprite) : ButtonDxCo(sprite) {
	this->model = model;
	this->on();
}

void RestartSurvivalButton::execute() {
	this->model->restartGame();
}

} /* namespace dxco */
