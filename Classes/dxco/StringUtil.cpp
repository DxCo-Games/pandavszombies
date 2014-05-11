#include "StringUtil.h"
#include <sstream>

namespace dxco {

std::string StringUtil::toString(int data) {
	std::ostringstream ss;
	ss << data;
	return ss.str();
}

std::string StringUtil::toString(float data) {
	std::ostringstream ss;
	ss << data;
	return ss.str();
}


int StringUtil::toInt(std::string data) {
	int value;
	std::istringstream ss(data);
	ss >> value;

	return value;
}

std::vector<std::string> StringUtil::split(const std::string &s, char delim) {

	std::vector<std::string> elems;

	std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }

    return elems;
}

} /* namespace dxco */
