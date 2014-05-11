#ifndef IMAGEFILEURLLOADER_H_
#define IMAGEFILEURLLOADER_H_

#include "cocos2d.h"
#include <string>

namespace dxco {

class ImageFileURLLoader {
public:
	ImageFileURLLoader(cocos2d::CCSprite* sprite, std::string filePath, std::string url, bool cache);

private:
	cocos2d::CCSprite* sprite;
	std::string filePath;
	std::string url;

	bool loadUsingFile();
};

} /* namespace dxco */
#endif /* IMAGEFILEURLLOADER_H_ */
