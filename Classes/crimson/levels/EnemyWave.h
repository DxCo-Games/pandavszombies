#ifndef ENEMYWAVE_H_
#define ENEMYWAVE_H_

#include <string>
#include <vector>

namespace dxco {

class GameModel;

class EnemyWave {
public:
	EnemyWave(GameModel *model, int total, float freq, int level, std::vector<std::string> types, int isBoss=0);
	EnemyWave(GameModel *model, int total, float freq, int level, std::vector<std::string> types, std::string killsType, float killsFreq=0.2, int isBoss=0);

	bool isFinished();
	void update(float dt);
	void reset();

	GameModel *model;
	int isBoss;
	int total;
	int count;
	int level;
	float freq; //seconds between enemies
	float dt; //seconds since last creation
	std::vector<std::string> types;
	std::string killsType;
	float killsFreq;

};

} /* namespace dxco */

#endif /* ENEMYWAVE_H_ */
