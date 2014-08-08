#include "FireWeapon.h"
#include "GameModel.h"

namespace dxco {

FireWeapon::FireWeapon(GameModel* model): Weapon(model) {
	this->bullets = 2000;
}

void FireWeapon::update(float dt) {
	this->bullets -= dt * 100;
}

void FireWeapon::shoot(){
	//do nothing
}

} /* namespace dxco */
