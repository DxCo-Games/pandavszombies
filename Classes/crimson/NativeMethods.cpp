#include "cocos2d.h"

#include "../dxco/DB.h"

#include <jni.h>

#ifndef _Included_com_dxco_crimson_NativeMethods
#define _Included_com_dxco_crimson_NativeMethods

extern "C" {

	JNIEXPORT void JNICALL Java_com_dxco_crimson_NativeMethods_goToRanking (JNIEnv *, jobject) {
		// DB::putInteger("ranking", 1);
	}

	JNIEXPORT void JNICALL Java_com_dxco_crimson_NativeMethods_goToGame (JNIEnv *, jobject) {
		// DB::putInteger("ranking", 0);
	}
}

#endif
