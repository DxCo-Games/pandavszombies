/*
 * LevelParser.cpp
 *
 *  Created on: Oct 9, 2014
 *      Author: gsosarolon
 */

#include "LevelParser.h"
#include "../GameModel.h"

namespace dxco {

std::vector<EnemyWave*> LevelParser::parse(GameModel* model, std::string levelPath) {

	std::vector<EnemyWave*> resultado;
	rapidjson::Document* document = JsonParser::parseJsonFile(levelPath);
	CCLOG("h1");
	for (rapidjson::SizeType i = 0; i < ((*document)["waves"]).Size(); i++) {
			CCLOG("h3");
			const rapidjson::Value& waveConfig = ((*document)["waves"])[i];

			int total = waveConfig["total"].GetInt();
			float freq = waveConfig["freq"].GetDouble();
			float speed = waveConfig["speed"].GetDouble();
			int isBoss = waveConfig["isBoss"].GetInt();

			CCLOG("Wave leida %i %f %f %i", total, freq, speed, isBoss);
			resultado.push_back(new EnemyWave(model, total, freq, speed, isBoss));
	}

	return resultado;
}
} /* namespace dxco */
