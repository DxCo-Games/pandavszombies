#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>

namespace dxco {

class EnemyWave;
class GameModel;

class Level {
public:
	Level(GameModel *model, std::vector<EnemyWave*>& waves);

	bool isFinished();
	void update(float dt);
	void restartLevel();

	//TODO add background creation to this?
	GameModel* model;
	std::vector<EnemyWave*> waves;
	int currentWave;
};

} /* namespace dxco */

#endif /* LEVEL_H_ */
