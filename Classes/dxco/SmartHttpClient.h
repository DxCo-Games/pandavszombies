#ifndef SMARTHTTPCLIENT_H_
#define SMARTHTTPCLIENT_H_

#include "cocos2d.h"
#include "../../extensions/network/HttpClient.h"

#include <string>

namespace dxco {

class SmartHttpClient : public cocos2d::CCObject {
public:
	virtual ~SmartHttpClient();

	void get(const std::string& url, const std::string& body = "");
	void post(const std::string& url, const std::string& body);

	void onGetRequestCompleted(cocos2d::extension::CCHttpClient* sender, void* data);
	void onPostRequestCompleted(cocos2d::extension::CCHttpClient* sender, void* data);

	virtual void executeGet(std::string responseData);
	virtual void executePost(std::string responseData);
};

} /* namespace dxco */
#endif /* SMARTHTTPCLIENT_H_ */
