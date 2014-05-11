#include "ImageFileURLLoader.h"
#include "ImageUrlLoader.h"
#include "FileUtil.h"
#include "SpriteUtil.h"

namespace dxco {

ImageFileURLLoader::ImageFileURLLoader(cocos2d::CCSprite* sprite, std::string filePath, std::string url, bool cache) {
	this->sprite = sprite;
	this->filePath = filePath;
	this->url = url;

	if (cache) {
		std::string fileContent = FileUtil::readFile(filePath);

		if (fileContent.size()) {
			SpriteUtil::setTexture(sprite, SpriteUtil::createTextuteWithBytes(fileContent));
		} else {
			CCLOG("posting");
			ImageUrlLoader* imageLoader = new ImageUrlLoader(sprite);
			imageLoader->setSavePath(filePath);
			imageLoader->get(url);
		}
	} else {
		ImageUrlLoader* imageLoader = new ImageUrlLoader(sprite);
		imageLoader->get(url);
	}
}

bool ImageFileURLLoader::loadUsingFile() {
	std::string fileContent = FileUtil::readFile(this->filePath);

	if (fileContent.size()) {
		cocos2d::CCTexture2D* texture = SpriteUtil::createTextuteWithBytes(fileContent);
		this->sprite->setTexture(texture);

		return true;
	} else {
		return false;
	}
}

} /* namespace dxco */
