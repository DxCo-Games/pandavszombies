#include "Hints.h"

namespace dxco {

Hints::Hints(GameModel* model) {
	this->model = model;

}


std::string Hints::getHint() {
	//TODO record number of straight loses survival/story
	std::string hint;

	hint = firstPowerup();
	if (hint != "") {
		return hint;
	}

	hint = powerup();
	if (hint != "") {
		return hint;
	}
	hint = playAnother();
	if (hint != "") {
		return hint;
	}

	hint = powerupForSurvival();
	if (hint != "") {
		return hint;
	}

	hint = superbossFireball();
	if (hint != "") {
		return hint;
	}

	hint = flamethrowerFrenzy();

	return hint;
}

std::string Hints::firstPowerup(){
	//if loses twice before buying the tutorial

	return "";
}
std::string Hints::powerup(){
	//if loses three and has money for +1 attack

	return "";
}
std::string Hints::playAnother(){
	//if loses 4 and has no money for +1 attack

	return "";
}
std::string Hints::powerupForSurvival(){
	//if loses survival in less than 2 min and has less than 3 attacks
	return "";
}
std::string Hints::superbossFireball(){
	//if loses twice to superboss and hasn't the fireball

	return "";
}
std::string Hints::flamethrowerFrenzy(){
	//if loses three in frenzy like and not flame or not bazooka

	return "";
}

} /* namespace dxco */
