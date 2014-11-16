#include "ResumeButton.h"

#include "../GameModel.h"
#include "../../HelloWorldScene.h"

namespace dxco {

ResumeButton::ResumeButton(GameModel* model, cocos2d::CCNode* sprite) : ButtonDxCo(sprite) {
	this->model = model;
	this->on();
}

void ResumeButton::execute() {
	this->model->vista->resumeGame();
}

} /* namespace dxco */
