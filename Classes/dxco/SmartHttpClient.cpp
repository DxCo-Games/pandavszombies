#include "SmartHttpClient.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace dxco {

void SmartHttpClient::get(const std::string& url, const std::string& body) {

	CCHttpRequest* httpRequest = new CCHttpRequest();

	httpRequest->setRequestType(CCHttpRequest::kHttpGet);
	httpRequest->setUrl(url.c_str());

	if (body.size()) {
		httpRequest->setRequestData(body.c_str(), strlen(body.c_str()));
	}

	httpRequest->setResponseCallback(this,
			httpresponse_selector(SmartHttpClient::onGetRequestCompleted));
	httpRequest->setTag("GET test");
	extension::CCHttpClient::getInstance()->setTimeoutForConnect(3000);
	extension::CCHttpClient::getInstance()->send(httpRequest);
	httpRequest->release();
}

void SmartHttpClient::post(const std::string& url, const std::string& body) {
	CCHttpRequest* httpRequest = new CCHttpRequest();

	httpRequest->setRequestType(CCHttpRequest::kHttpPost);
	httpRequest->setUrl(url.c_str());

	if (body.size()) {
		httpRequest->setRequestData(body.c_str(), strlen(body.c_str()));
	}

	httpRequest->setResponseCallback(this,
			httpresponse_selector(SmartHttpClient::onPostRequestCompleted));
	httpRequest->setTag("POST test");

	extension::CCHttpClient::getInstance()->setTimeoutForConnect(3000);
	extension::CCHttpClient::getInstance()->send(httpRequest);

	httpRequest->release();
}

void SmartHttpClient::onGetRequestCompleted(CCHttpClient* sender, void* data) {
	CCHttpResponse* response = (CCHttpResponse*) data;
	if (!response) {
		return;
	}

	if (0 != strlen(response->getHttpRequest()->getTag())) {
		CCLog("%s completed", response->getHttpRequest()->getTag());
	}

	int statusCode = response->getResponseCode();
	CCLog("Status Code: %d", statusCode);

	if (!response->isSucceed()) {
		CCLog("response failed, error buffer: %s", response->getErrorBuffer());
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	std::string temp(buffer->begin(), buffer->end());
	executeGet(temp);
}

void SmartHttpClient::onPostRequestCompleted(
		cocos2d::extension::CCHttpClient* sender, void* data) {

	CCHttpResponse* response = (CCHttpResponse*) data;
	if (!response) {
		return;
	}

	if (0 != strlen(response->getHttpRequest()->getTag())) {
		CCLog("%s completed", response->getHttpRequest()->getTag());
	}

	int statusCode = response->getResponseCode();
	CCLog("Status Code: %d", statusCode);

	if (!response->isSucceed()) {
		CCLog("response failed, error buffer: %s", response->getErrorBuffer());
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	std::string temp(buffer->begin(), buffer->end());

	executePost(temp);
}

void SmartHttpClient::executeGet(std::string responseData) {
	CCLog("GET DATA: %s", responseData.c_str());
}

void SmartHttpClient::executePost(std::string responseData) {
	CCLog("POST DATA: %s", responseData.c_str());
}

SmartHttpClient::~SmartHttpClient() {
	extension::CCHttpClient::getInstance()->destroyInstance();
}

} /* namespace dxco */
