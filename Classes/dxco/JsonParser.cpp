#include "JsonParser.h"
#include "FileUtil.h"
#include "cocos2d.h"

namespace dxco {

rapidjson::Document* JsonParser::parseJson(std::string& json) {

	rapidjson::Document* document = new rapidjson::Document();
	document->Parse<0>(json.c_str());

	cocos2d::CCLog("tiene errores? %i" , document->HasParseError());

	return document;
}

rapidjson::Document* JsonParser::parseJsonFile(std::string& filePath) {

	unsigned long int size;
	unsigned char* contentData = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(
			filePath.c_str(), "r", &size);

	std::string data;
	data.append((char*)contentData, (int)size);

	return JsonParser::parseJson(data);
}

} /* namespace dxco */
