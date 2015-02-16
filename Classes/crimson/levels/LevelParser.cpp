#include "LevelParser.h"
#include "EnemyWave.h"
#include "TimedLevel.h"
#include "KillCountLevel.h"
#include "../GameModel.h"
#include "../bonus/NoBonusFactory.h"
#include "../bonus/WeaponFirstBonusFactory.h"
#include "../../HelloWorldScene.h"

namespace dxco {

Level* LevelParser::parse(GameModel* model, std::string levelPath, int currentLevel) {

	std::vector<EnemyWave*> resultado;
	rapidjson::Document* document = JsonParser::parseJsonFile(levelPath);
	int map = (*document)["config"]["background"].GetInt();
	model->vista->setMap(map);
	for (rapidjson::SizeType i = 0; i < ((*document)["waves"]).Size(); i++) {
			const rapidjson::Value& waveConfig = ((*document)["waves"])[i];

			int total = waveConfig["total"].GetInt();

			float freq = waveConfig["freq"].GetDouble();
			int isBoss = waveConfig["isBoss"].GetInt();

			std::vector<std::string> vec;
			if (waveConfig.HasMember("types")) {
				for (rapidjson::SizeType j = 0; j < waveConfig["types"].Size(); j++) {
					vec.push_back( waveConfig["types"][j].GetString());
				}
			}
			if (waveConfig.HasMember("killsFreq")) {
				float killsFreq = waveConfig["killsFreq"].GetDouble();
				std::string killsType = (*document)["config"]["type"].GetString();
				resultado.push_back(new EnemyWave(model, total, freq, currentLevel, vec, killsType, killsFreq));
			} else {
				resultado.push_back(new EnemyWave(model, total, freq, currentLevel, vec, isBoss));
			}
	}

	std::string title = "";
	if ((*document)["config"].HasMember("title")) {
		title = (*document)["config"]["title"].GetString();
	}

	Level *level;
	if ((*document)["config"].HasMember("kills")) {
		int kills = (*document)["config"]["kills"].GetInt();
		std::string type = (*document)["config"]["type"].GetString();
		level = new KillCountLevel(model, resultado, kills, type, title);
	} else if((*document)["config"].HasMember("time")) {
		int time = (*document)["config"]["time"].GetInt();
		level = new TimedLevel(model, resultado, time, title);
	} else {
		level = new Level(model, resultado, title);
	}

	if ((*document)["config"].HasMember("bonus")) {
		int bonus = (*document)["config"]["bonus"].GetInt();
		if (bonus == 1) {
			level->bonusFactory = new WeaponFirstBonusFactory();
		} else if (bonus == 2) {
			level->bonusFactory = new NoBonusFactory();
		}
	}

	return level;


}
} /* namespace dxco */
