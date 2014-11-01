#ifndef ENEMYWAVE_H_
#define ENEMYWAVE_H_

#include <string>
#include <vector>

namespace dxco {

class GameModel;

class EnemyWave {
public:
	EnemyWave(GameModel *model, int total, float freq, int level, std::vector<std::string> types, bool isBoss=false);

	bool isFinished();
	void update(float dt);
	void reset();

	GameModel *model;
	bool isBoss; //TODO makes sense?
	int total;
	int count;
	int level;
	float freq; //seconds between enemies
	float dt; //seconds since last creation
	std::vector<std::string> types;

};

} /* namespace dxco */

#endif /* ENEMYWAVE_H_ */
