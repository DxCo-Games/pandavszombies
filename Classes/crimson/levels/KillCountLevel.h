#ifndef KILLCOUNTLEVEL_H_
#define KILLCOUNTLEVEL_H_

#include "Level.h"
#include <string>

namespace dxco {

//Story mode level that finishes after a fixed amount of enemies have been killed
class KillCountLevel: public Level {
public:
	KillCountLevel(GameModel *model, std::vector<EnemyWave*>& waves, int kills, std::string type, std::string title="");

	virtual bool isFinished();
	virtual void updateInterface();
	std::string verboseType();

	virtual void showMessage();
	std::string getTypeIndex();
	int kills;
	std::string type;
};

} /* namespace dxco */

#endif /* KILLCOUNTLEVEL_H_ */
