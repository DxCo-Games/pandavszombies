#include "ShareButton.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "../GameModel.h"
#include "../../HelloWorldScene.h"

namespace dxco {

ShareButton::ShareButton(cocos2d::CCSprite* sprite, GameModel* model) : ButtonDxCo(sprite) {
	this->on();
	this->model = model;

}

std::string ShareButton::takeScreenshot() {
	cocos2d::CCSize screenSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
	cocos2d::CCRenderTexture * tex = cocos2d::CCRenderTexture::create(screenSize.width, screenSize.height);
	tex->setPosition(ccp(screenSize.width/2, screenSize.height/2));

	//hardcode damn cocos never creates its writable path
	std::string filename = "/sdcard/Android/data/share_screenshot.png";

	tex->begin();
	model->vista->getParent()->visit();
	cocos2d::CCImage* img = tex->newCCImage(true);
	img->saveToFile(filename.c_str(), true);
	CC_SAFE_DELETE(img);
	tex->end();

	return filename;
}

//TODO improve text
//TODO include level info in text
//TODO ocultar botones

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void ShareButton::execute() {

	std::string path = takeScreenshot();
	CCLOG("SENDING %s", path.c_str());
	std::string msg = "I've just played some level in http://bit.ly/PandaVZ";

	cocos2d::JniMethodInfo t;

	if (cocos2d::JniHelper::getStaticMethodInfo(t,
					"com/dxco/pandavszombies/CppConnectorActivity",
					"share",
					"(Ljava/lang/String;Ljava/lang/String;)V")) {

		jstring StringArg1 = t.env->NewStringUTF(path.c_str());
		jstring StringArg2 = t.env->NewStringUTF(msg.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, StringArg1, StringArg2);
		t.env->DeleteLocalRef(StringArg1);
		t.env->DeleteLocalRef(StringArg2);
		t.env->DeleteLocalRef(t.classID);
	}
}
#else
#endif

} /* namespace dxco */
