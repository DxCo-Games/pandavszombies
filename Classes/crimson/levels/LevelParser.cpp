#include "LevelParser.h"
#include "EnemyWave.h"
#include "TimedLevel.h"
#include "KillCountLevel.h"
#include "../GameModel.h"
#include "../../HelloWorldScene.h"

namespace dxco {

Level* LevelParser::parse(GameModel* model, std::string levelPath) {

	std::vector<EnemyWave*> resultado;
	rapidjson::Document* document = JsonParser::parseJsonFile(levelPath);
	int map = (*document)["config"]["background"].GetInt();
	model->vista->setMap(map);
	for (rapidjson::SizeType i = 0; i < ((*document)["waves"]).Size(); i++) {
			CCLOG("h3");
			const rapidjson::Value& waveConfig = ((*document)["waves"])[i];

			int total = waveConfig["total"].GetInt();
			float freq = waveConfig["freq"].GetDouble();
			float level = waveConfig["level"].GetInt();
			int isBoss = waveConfig["isBoss"].GetInt();

			CCLOG("Wave leida %i %f %i %i", total, freq, level, isBoss);
			std::vector<std::string> vec;
			if (waveConfig.HasMember("types")) {
				for (rapidjson::SizeType j = 0; j < waveConfig["types"].Size(); j++) {
					vec.push_back( waveConfig["types"][j].GetString());
				}
			}
			resultado.push_back(new EnemyWave(model, total, freq, level, vec, isBoss));
	}

	if ((*document)["config"].HasMember("kills")) {
		int kills = (*document)["config"]["kills"].GetInt();
		std::string type = (*document)["config"]["type"].GetString();
		return new KillCountLevel(model, resultado, kills, type);
	} else if((*document)["config"].HasMember("time")) {
		int time = (*document)["config"]["time"].GetInt();
		return new TimedLevel(model, resultado, time);
	} else {
		return new Level(model, resultado);
	}


}
} /* namespace dxco */
