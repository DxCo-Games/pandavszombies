#include "DB.h"

namespace dxco {

void DB::putString(const std::string& key, const std::string& value) {
	cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey(key.c_str(), value);
	cocos2d::CCUserDefault::sharedUserDefault()->flush();
}

void DB::putInteger(const std::string& key, const int& value) {
	cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey(key.c_str(), value);
	cocos2d::CCUserDefault::sharedUserDefault()->flush();
}

std::string DB::getString(const std::string& key) {
	return cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey(key.c_str());
}

int DB::getInteger(const std::string& key) {
	return cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey(key.c_str());
}

} /* namespace dxco */
