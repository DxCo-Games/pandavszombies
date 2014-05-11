#ifndef IMAGEURLLOADER_H_
#define IMAGEURLLOADER_H_

#include "cocos2d.h"
#include "SmartHttpClient.h"

namespace dxco {

class ImageUrlLoader : public SmartHttpClient {

public:
	ImageUrlLoader(cocos2d::CCSprite* sprite);
	void executeGet(std::string responseData);
	void setSavePath(std::string savePath);
private:
	cocos2d::CCSprite* sprite;
	std::string savePath;
};

} /* namespace dxco */
#endif /* IMAGEURLLOADER_H_ */
