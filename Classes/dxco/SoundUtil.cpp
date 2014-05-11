#include "SoundUtil.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

namespace dxco {

bool SoundUtil::isSoundOn() {

	bool result = false;

	cocos2d::JniMethodInfo t;

	if (cocos2d::JniHelper::getStaticMethodInfo(t,
				"com/dxco/SoundUtil", "isSoundOnCpp",
				"()I")) {

		int ret = (int) t.env->CallStaticIntMethod(t.classID, t.methodID);

		if (ret) {
			result = true;
		}
	}

	return result;
}

} /* namespace dxco */
