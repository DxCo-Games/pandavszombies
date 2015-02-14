#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <string>

namespace dxco {

class EnemyWave;
class GameModel;
class BonusFactory;

class Level {
public:
	Level(GameModel *model, std::vector<EnemyWave*>& waves, std::string title="");

	virtual bool isFinished();
	virtual void update(float dt);
	virtual void updateFreezed(float dt);
	virtual void restartLevel();

	virtual void updateInterface();

	//TODO add background creation to this?
	GameModel* model;
	BonusFactory* bonusFactory;
	std::vector<EnemyWave*> waves;
	int currentWave;
	int totalEnemies;
	std::string title;
};

} /* namespace dxco */

#endif /* LEVEL_H_ */
