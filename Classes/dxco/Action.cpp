#include "Action.h"

namespace dxco {

Action::Action() {
	this->finished = false;
}

bool Action::isFinished() {
	return this->finished;
}

void Action::run(float dt) {
	this->finished = true;
}

Action::~Action() {

}

} /* namespace dxco */
