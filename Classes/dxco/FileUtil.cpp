#include "FileUtil.h"

#include <fstream>
#include <sstream>
#include "cocos2d.h"

namespace dxco {

std::string FileUtil::readFile(std::string& path) {

	std::string pathWritable = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
	pathWritable += path;
	std::ifstream t(pathWritable.c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();

	return buffer.str();
}

bool FileUtil::writeFile(std::string& path, std::string& content) {

	if (content.size()) {
		std::ofstream file;
		std::string pathWritable = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
		pathWritable += path;

		file.open(pathWritable.c_str(), std::ios::out | std::ios::binary);
		file << content;

		file.close();
	}
}

} /* namespace dxco */
