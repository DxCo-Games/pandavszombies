#include "AdsAPI.h"

#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

namespace dxco {

	void AdsAPI::showAd() {

		cocos2d::JniMethodInfo t;

		if (cocos2d::JniHelper::getStaticMethodInfo(t, "com/dxco/DxcoCpp", "showInterstitial", "()V")) {
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
		}
	}

} /* namespace dxco */
