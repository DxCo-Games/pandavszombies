#ifndef GAMEPROPERTIES_H_
#define GAMEPROPERTIES_H_

#include <map>
#include <string>
#define DB_VERSION 1920
#define ITEM_INITIAL_COST 250

namespace dxco {

class GameProperties {
public:
	//get parameters from level?

	static int get(std::string key);
	static void set(std::string key, int value);
	static void powerUp(std::string key, int level);

	// this function takes the saved property percentage
	static void powerUp(std::string key);
	static int increaseLevel(std::string key);

	static std::map<std::string, float> prop;

	static void saveDefaultProperties();
	static void init();

	static int getPrice(std::string);
};

} /* namespace dxco */

#endif /* GAMEPROPERTIES_H_ */
