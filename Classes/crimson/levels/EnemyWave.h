#ifndef ENEMYWAVE_H_
#define ENEMYWAVE_H_

#include <string>

namespace dxco {

class GameModel;

class EnemyWave {
public:
	//TODO take the parameters from another place rather than constructor
	//TODO add parameters: allowed characters (cura, basquet, etc.) wave duration
	EnemyWave(GameModel *model, int total, float freq, int level, bool isBoss=false);

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

};

} /* namespace dxco */

#endif /* ENEMYWAVE_H_ */
