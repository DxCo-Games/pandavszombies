#ifndef GAMEPROPERTIES_H_
#define GAMEPROPERTIES_H_

#include <map>
#include <string>

namespace dxco {

class GameProperties {
public:
	//get default parameters
	GameProperties();
	//get parameters from level?

	float get(std::string key);
	void set(std::string key, float value);
	void powerUp(std::string key, float percentage);

	std::map<std::string, float> prop;
};

} /* namespace dxco */

#endif /* GAMEPROPERTIES_H_ */
