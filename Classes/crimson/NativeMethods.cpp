#include "cocos2d.h"

#include "../dxco/DB.h"

#include <jni.h>

#ifndef _Included_com_dxco_crimson_NativeMethods
#define _Included_com_dxco_crimson_NativeMethods

extern "C" {

	JNIEXPORT void JNICALL Java_com_dxco_crimson_NativeMethods_goToRanking (JNIEnv *, jobject) {
		dxco::DB::putString("goTo", "ranking");
	}

	JNIEXPORT void JNICALL Java_com_dxco_crimson_NativeMethods_goToChallenge (JNIEnv *, jobject) {
		dxco::DB::putString("goTo", "challenge");
	}

	JNIEXPORT void JNICALL Java_com_dxco_crimson_NativeMethods_goToStory (JNIEnv *, jobject) {
		dxco::DB::putString("goTo", "story");
	}

	JNIEXPORT void JNICALL Java_com_dxco_crimson_NativeMethods_goToSurvival (JNIEnv *, jobject) {
		dxco::DB::putString("goTo", "survival");
	}
}

#endif
