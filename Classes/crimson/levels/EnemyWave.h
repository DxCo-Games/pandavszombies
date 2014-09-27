#ifndef ENEMYWAVE_H_
#define ENEMYWAVE_H_

#include <string>

namespace dxco {

class GameModel;

class EnemyWave {
public:
	EnemyWave(GameModel *model, int total, float freq, float speed, bool isBoss=false);

	//get property values for the wave. TODO better a string to be casted?
//	float get(std::string propertyName);
//	float get(std::string propertyName, float defaultValue);

	bool isFinished();
	void update(float dt);
	void reset();

	GameModel *model;
	bool isBoss; //TODO makes sense?
	int total;
	int count;
	float speed;
	float freq; //seconds between enemies
	float dt; //seconds since last creation

};

} /* namespace dxco */

#endif /* ENEMYWAVE_H_ */
