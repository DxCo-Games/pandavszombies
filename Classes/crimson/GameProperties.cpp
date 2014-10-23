#include "GameProperties.h"

namespace dxco {

GameProperties::GameProperties() {
	//default properties
	this->prop["enemy.level"] = 1;
	this->prop["player.life"] = 200;
	this->prop["player.speed"] = 90;
	this->prop["bonus.probability"] = 10;

	//TODO check this in bonus factory
	this->prop["bazooka.unlocked"] = 1;
	this->prop["fire.unlocked"] = 1;
	this->prop["firebullet.unlocked"] = 1;

	this->prop["weapon.duration"] = 15;
	this->prop["bullet.damage"] = 10;
	this->prop["bazooka.damage"] = 80;
	this->prop["explosion.damage"] = 80;
}

float GameProperties::get(std::string key) {
	return this->prop[key];
}
void GameProperties::set(std::string key, float value) {
	this->prop[key] = value;
}
void GameProperties::powerUp(std::string key, float percentage) {
	this->prop[key] += this->prop[key] * percentage;
}

} /* namespace dxco */
