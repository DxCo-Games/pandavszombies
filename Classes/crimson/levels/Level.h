#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>

namespace dxco {

class EnemyWave;
class GameModel;

class Level {
public:
	Level(GameModel *model, std::vector<EnemyWave*>& waves);

	virtual bool isFinished();
	virtual void update(float dt);
	virtual void restartLevel();

	//TODO add background creation to this?
	GameModel* model;
	std::vector<EnemyWave*> waves;
	int currentWave;
};

} /* namespace dxco */

#endif /* LEVEL_H_ */
