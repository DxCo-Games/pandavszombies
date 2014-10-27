#include "LevelParser.h"
#include "EnemyWave.h"
#include "../GameModel.h"

namespace dxco {

Level* LevelParser::parse(GameModel* model, std::string levelPath) {

	std::vector<EnemyWave*> resultado;
	rapidjson::Document* document = JsonParser::parseJsonFile(levelPath);
	CCLOG("h1");
	for (rapidjson::SizeType i = 0; i < ((*document)["waves"]).Size(); i++) {
			CCLOG("h3");
			const rapidjson::Value& waveConfig = ((*document)["waves"])[i];

			int total = waveConfig["total"].GetInt();
			float freq = waveConfig["freq"].GetDouble();
			float level = waveConfig["level"].GetInt();
			int isBoss = waveConfig["isBoss"].GetInt();

			CCLOG("Wave leida %i %f %i %i", total, freq, level, isBoss);
			resultado.push_back(new EnemyWave(model, total, freq, level, isBoss));
	}

	return new Level(model, resultado);
}
} /* namespace dxco */
