#include "GameProperties.h"

#include "../dxco/DB.h"
#include "../dxco/StringUtil.h"
#include <string>
#include "cocos2d.h"

#include <math.h>

namespace dxco {

void GameProperties::init() {

	int saveDefaultProperties = DB::getInteger("save_default_properties");

	if (saveDefaultProperties != DB_VERSION) {
		GameProperties::saveDefaultProperties();
	}
}

void GameProperties::saveDefaultProperties() {
	//default properties
	DB::putInteger("enemy.level", 1);

	DB::putInteger("player.life", 200);
	DB::putInteger("player.speed", 90);
	DB::putInteger("bonus.probability", 10);

	DB::putInteger("weapon.duration", 15);
	DB::putInteger("attack.damage", 10);

	DB::putInteger("bazooka.unlocked", 0);
	DB::putInteger("fire.unlocked", 0);
	DB::putInteger("firebullet.unlocked", 0);
	DB::putInteger("frenzy.unlocked", 0);


	// Indica el nivel de la mejor. Inicialmente en 0, luego 1, 2, 3, 4, ...
	DB::putInteger("player.life.level", 1);
	DB::putInteger("player.speed.level", 1);
	DB::putInteger("bonus.probability.level", 1);

	DB::putInteger("weapon.duration.level", 1);
	DB::putInteger("attack.damage.level", 1);

	// cuando se realiza una mejora, la propiedad mejora en este porcentaje.
	DB::putInteger("player.life.addition", 50);
	DB::putInteger("player.speed.addition", 2);
	DB::putInteger("bonus.probability.addition", 4);

	DB::putInteger("weapon.duration.addition", 10);
	DB::putInteger("attack.damage.addition", 10);

	DB::putInteger("save_default_properties", DB_VERSION);
}

int GameProperties::get(std::string key) {
	GameProperties::init();
	return DB::getInteger(key);
}

void GameProperties::set(std::string key, int value) {
	GameProperties::init();
	DB::putInteger(key, value);
}


void GameProperties::powerUp(std::string key) {
	if (key == "bazooka.unlocked" || key == "fire.unlocked" || key == "firebullet.unlocked" || key == "frenzy.unlocked") {
		DB::putInteger(key, 1);
	} else {
		int currentLevel = GameProperties::increaseLevel(key);
		GameProperties::powerUp(key, currentLevel);
	}

}

int	 GameProperties::increaseLevel(std::string key) {
	int currentLevel = DB::getInteger(key + std::string(".level"));
	currentLevel++;

	DB::putInteger(key + std::string(".level"), currentLevel);

	return currentLevel;
}

void GameProperties::powerUp(std::string key, int level) {
	int currentValue = GameProperties::get(key);
	int addition = DB::getInteger(key + std::string(".addition"));

	int nextValue = currentValue + addition;

	if (nextValue == currentValue) {
		// addition never should be zero.
		nextValue++;
	}

	CCLOG("Powerup %s %d %i %i", key.c_str(), addition, currentValue, nextValue);
	GameProperties::set(key, nextValue);
}

int GameProperties::getPrice(std::string key) {
	float level = (float)GameProperties::get(key + std::string(".level")) - 1;
	level /= 1.618033988749; //numero de dios =(

	if (key == "firebullet.unlocked") {
		return 1500;
	} else if (key == "bazooka.unlocked") {
		return 2500;
	} else if (key == "fire.unlocked") {
		return 5200;
	} else if (key == "frenzy.unlocked") {
		return 10000;
	}

	// numero de dios =(
	double multiplier = pow (1.618033988749, level);

	return 500 * multiplier;
}

} /* namespace dxco */
