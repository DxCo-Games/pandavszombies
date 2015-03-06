#include "ParseConfiguration.h"
#include "cocos2d.h"

#include "platform/android/jni/JniHelper.h"

#include <jni.h>

namespace dxco {

int ParseConfiguration::getAdMinLevel() {

	cocos2d::JniMethodInfo t;

	if (cocos2d::JniHelper::getStaticMethodInfo(t, "com/dxco/pandavszombies/ParseConfiguration", "getAdMinLevel", "()I")) {

		return (int) t.env->CallStaticIntMethod(t.classID, t.methodID);
	}

	return 15;
}

int ParseConfiguration::getShowAdRateSurvival() {

	cocos2d::JniMethodInfo t;

	if (cocos2d::JniHelper::getStaticMethodInfo(t, "com/dxco/pandavszombies/ParseConfiguration", "getShowAdRateSurvival", "()I")) {

		return (int) t.env->CallStaticIntMethod(t.classID, t.methodID);
	}

	return 15;
}

int ParseConfiguration::getShowAdRateStory() {

	cocos2d::JniMethodInfo t;

	if (cocos2d::JniHelper::getStaticMethodInfo(t, "com/dxco/pandavszombies/ParseConfiguration", "getShowAdRateStory", "()I")) {

		return (int) t.env->CallStaticIntMethod(t.classID, t.methodID);
	}

	return 15;
}

} /* namespace dxco */
