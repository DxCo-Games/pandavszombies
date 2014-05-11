#include "ImageUrlLoader.h"
#include "SpriteUtil.h"
#include "FileUtil.h"
namespace dxco {


ImageUrlLoader::ImageUrlLoader(cocos2d::CCSprite* sprite) {
	this->sprite = sprite;
}

void ImageUrlLoader::executeGet(std::string responseData) {
	this->sprite->setTexture(SpriteUtil::createTextuteWithBytes(responseData));

	if (!this->savePath.empty()) {
		FileUtil::writeFile(this->savePath, responseData);
	}
}

void ImageUrlLoader::setSavePath(std::string savePath) {
	this->savePath = savePath;
}

} /* namespace dxco */
