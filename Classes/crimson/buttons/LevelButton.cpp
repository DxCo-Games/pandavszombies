#include "LevelButton.h"
#include "../../dxco/SpriteUtil.h"

namespace dxco {

LevelButton::LevelButton(int number, float x, float y) {
	this->number = number;

	//TODO if level not in db then not enabled
	//TODO if level in db get stars
	this->sprite = SpriteUtil::create("buttons/LEVELS-x0.png", x, y);
	this->on();
}

void LevelButton::execute() {
	//TODO call hello world in mode story with given level number
}


} /* namespace dxco */
