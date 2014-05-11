#include "FacebookAPI.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

namespace dxco {

extern "C" {

std::string FacebookAPI::getAccessToken() {

	std::string resultado = "";

	cocos2d::JniMethodInfo t;

	if (cocos2d::JniHelper::getStaticMethodInfo(t,
			"com/dxco/facebook/FacebookAPI", "getAccessToken",
			"()Ljava/lang/String;")) {

		jstring ret = (jstring) t.env->CallObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		jboolean is_copy = 0;
		const char* str = t.env->GetStringUTFChars(ret, &is_copy);

		if (str) {
			resultado = str;
		}

		if (is_copy) {
			t.env->ReleaseStringUTFChars(ret, str);
		}

		t.env->DeleteLocalRef(ret);

	}

	return resultado;
}

std::string FacebookAPI::getUserID() {
	std::string resultado = "";

	cocos2d::JniMethodInfo t;

	if (cocos2d::JniHelper::getStaticMethodInfo(t,
			"com/dxco/facebook/FacebookAPI", "getUserID",
			"()Ljava/lang/String;")) {

		jstring ret = (jstring) t.env->CallObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		jboolean is_copy = 0;
		const char* str = t.env->GetStringUTFChars(ret, &is_copy);

		if (str) {
			resultado = str;
		}

		if (is_copy) {
			t.env->ReleaseStringUTFChars(ret, str);
		}

		t.env->DeleteLocalRef(ret);

	}

	return resultado;
}

std::string FacebookAPI::getUsername() {
	std::string resultado = "";

	cocos2d::JniMethodInfo t;

	if (cocos2d::JniHelper::getStaticMethodInfo(t,
			"com/dxco/facebook/FacebookAPI", "getUsername",
			"()Ljava/lang/String;")) {

		jstring ret = (jstring) t.env->CallObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		jboolean is_copy = 0;
		const char* str = t.env->GetStringUTFChars(ret, &is_copy);

		if (str) {
			resultado = str;
		}

		if (is_copy) {
			t.env->ReleaseStringUTFChars(ret, str);
		}

		t.env->DeleteLocalRef(ret);

	}

	return resultado;
}

std::string FacebookAPI::getLastName() {
	std::string resultado = "";

	cocos2d::JniMethodInfo t;

	if (cocos2d::JniHelper::getStaticMethodInfo(t,
			"com/dxco/facebook/FacebookAPI", "getLastName",
			"()Ljava/lang/String;")) {

		jstring ret = (jstring) t.env->CallObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		jboolean is_copy = 0;
		const char* str = t.env->GetStringUTFChars(ret, &is_copy);

		if (str) {
			resultado = str;
		}

		if (is_copy) {
			t.env->ReleaseStringUTFChars(ret, str);
		}

		t.env->DeleteLocalRef(ret);

	}

	return resultado;
}

std::string FacebookAPI::getFirstName() {
	std::string resultado = "";

	cocos2d::JniMethodInfo t;

	if (cocos2d::JniHelper::getStaticMethodInfo(t,
			"com/dxco/facebook/FacebookAPI", "getFirstName",
			"()Ljava/lang/String;")) {

		jstring ret = (jstring) t.env->CallObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		jboolean is_copy = 0;
		const char* str = t.env->GetStringUTFChars(ret, &is_copy);

		if (str) {
			resultado = str;
		}

		if (is_copy) {
			t.env->ReleaseStringUTFChars(ret, str);
		}

		t.env->DeleteLocalRef(ret);

	}

	return resultado;
}


void FacebookAPI::rate() {
	cocos2d::JniMethodInfo t;

	if (cocos2d::JniHelper::getStaticMethodInfo(t, "com/dxco/SocialUtil",
			"startRateAppIntentFromMenu", "()I")) {

		t.env->CallStaticIntMethod(t.classID, t.methodID);
	}
}


void FacebookAPI::invite() {
	cocos2d::JniMethodInfo t;

	if (cocos2d::JniHelper::getStaticMethodInfo(t, "com/dxco/facebook/FacebookAPI", "invite",
			"()I")) {
		t.env->CallStaticIntMethod(t.classID, t.methodID);
	}
}

bool FacebookAPI::hasFacebookSession() {
	bool result = false;

	cocos2d::JniMethodInfo t;

	if (cocos2d::JniHelper::getStaticMethodInfo(t,
				"com/dxco/facebook/FacebookAPI", "hasSession",
				"()I")) {

		int ret = (int) t.env->CallStaticIntMethod(t.classID, t.methodID);

		if (ret) {
			result = true;
		}
	}

	return result;
}

}
} /* namespace dxco */
