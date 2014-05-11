#ifndef JSONPARSER_H_
#define JSONPARSER_H_

#include "rapidjson/document.h"

#include <string>

namespace dxco {

/**
 * Information on rapidjson can be found here: https://code.google.com/p/rapidjson/wiki/UserGuide
 */
class JsonParser {
public:
	static rapidjson::Document* parseJson(std::string& json);
	static rapidjson::Document* parseJsonFile(std::string& filePath);
};

} /* namespace dxco */
#endif /* JSONPARSER_H_ */
