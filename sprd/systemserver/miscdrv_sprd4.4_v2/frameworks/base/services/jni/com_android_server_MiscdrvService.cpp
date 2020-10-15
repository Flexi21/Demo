/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "MiscdrvServiceJni"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>
#include <hardware/hardware.h>
#include <hardware/miscdrv.h>
#include <linux/rtc.h>

#include <stdio.h>

namespace android {
jclass jclassrtctime;

#if defined(JM_MISCDRV_SUPPORT) //Leo 20201009
miscdrv_device_t *d_miscdrv;

static jint android_server_MiscdrvSer_JniOpen(JNIEnv *env, jobject clazz)
{
	hw_module_t const* module;
	int err;

	ALOGD("miscdrv: %s Entry!\n",__func__);

	err = hw_get_module(MISCDRV_HARDWARE_MODULE_ID, &module);
	if (err != 0) {
		ALOGE("Can't get module id MISCDRV_HARDWARE_MODULE_ID, error: %d", err);
		return 0;
	}

	err = module->methods->open(module, MISCDRV_HARDWARE_MODULE_ID, (hw_device_t **) &d_miscdrv);
	if (err < 0) {
		ALOGE("Can't open MISCDRV_HARDWARE_MODULE_ID, error: %d", err);
		return 0;
	}
	
	return 0;
}
	
static void android_server_MiscdrvSer_JniDummy(JNIEnv *env, jobject clazz)
{
	ALOGD("miscdrv: %s Entry!\n",__func__);
	
	d_miscdrv->miscdrv_dummy();
}

static void android_server_MiscdrvSer_JniLedCtrl(JNIEnv *env, jobject clazz, 
                                           jint type, jint brightness, jint on_ms, jint off_ms)
{
	ALOGD("miscdrv: %s Entry!\n",__func__);
	
	d_miscdrv->miscdrv_led_ctrl(type, brightness, on_ms, off_ms);
}

static jobject android_server_MiscdrvSer_JniReadtime(JNIEnv *env, jobject clazz)
{
	int ret = -1;
	struct tm tm;
	
	ALOGD("miscdrv: %s Entry!\n",__func__);
	jclass jclazz  = env->FindClass("android/os/RtcTime"); 
	jclassrtctime = (jclass)env->NewGlobalRef(jclazz);
	jmethodID jidRtcTime = env->GetMethodID(jclazz, "<init>", "(IIIIIII)V");
	
	#if 0 //just for debug_
	tm.tm_year = 2020;
	tm.tm_mon = 9;
	tm.tm_mday = 29;
	tm.tm_hour = 14;
	tm.tm_min = 26;
	tm.tm_sec = 15;
	#else
	ret = d_miscdrv->miscdrv_rtc_readtime(&tm);
	if (ret != 0) {
		ALOGE("miscdrv: %s readtime error!\n",__func__);
	}
	#endif
	 
	jobject result = env->NewObject(jclassrtctime, jidRtcTime, tm.tm_year + 1900, 
	          tm.tm_mon + 1, tm.tm_mday, tm.tm_wday, tm.tm_hour, tm.tm_min, tm.tm_sec); 
	return result;
}

static int android_server_MiscdrvSer_JniSettime(JNIEnv *env, jobject clazz, 
              jint year, jint mon, jint mday, jint wday, jint hour, jint min, jint sec)
{
	int ret;
	struct tm tm;

	ALOGD("miscdrv: %s Entry!\n",__func__);

	tm.tm_year  = year - 1900;
	tm.tm_mon   = mon - 1;
	tm.tm_mday  = mday;
	tm.tm_wday  = wday;
	tm.tm_hour  = hour;
	tm.tm_min   = min;
	tm.tm_sec   = sec;

	ret = d_miscdrv->miscdrv_rtc_settime(tm);
	if (ret != 0) {
		ALOGE("miscdrv: %s settime error!\n",__func__);
		return -1;
	}

	ALOGE("settime %d:%d:%d  %d:%d %d\n",tm.tm_year,
				tm.tm_mon,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);

	return 0;
}

static void android_server_MiscdrvSer_JniSetWdClk(JNIEnv *env, jobject clazz, jint val)
{
	ALOGD("miscdrv: %s Entry!\n",__func__);
	d_miscdrv->miscdrv_wdt_clk(val);
}
#else
static jint android_server_MiscdrvSer_JniOpen(JNIEnv *env, jobject clazz)
{
	ALOGD("miscdrv: %s empty Entry!\n",__func__);
	return 0;
}

static void android_server_MiscdrvSer_JniDummy(JNIEnv *env, jobject clazz)
{
	ALOGD("miscdrv: %s empty Entry!\n",__func__);
}

static void android_server_MiscdrvSer_JniLedCtrl(JNIEnv *env, jobject clazz, 
                                           jint type, jint brightness, jint on_ms, jint off_ms)
{
	ALOGD("miscdrv: %s empty Entry!\n",__func__);
}

static jobject android_server_MiscdrvSer_JniReadtime(JNIEnv *env, jobject clazz)
{
	int ret = -1;
	struct tm tm;
	
	ALOGD("miscdrv: %s empty Entry!\n",__func__);
	jclass jclazz  = env->FindClass("android/os/RtcTime"); 
	jclassrtctime = (jclass)env->NewGlobalRef(jclazz);
	jmethodID jidRtcTime = env->GetMethodID(jclazz, "<init>", "(IIIIIII)V");
	
	#if 1 //just for debug_
	tm.tm_year = 2020;
	tm.tm_mon = 9;
	tm.tm_mday = 29;
	tm.tm_hour = 14;
	tm.tm_min = 26;
	tm.tm_sec = 15;
	#else
	ret = d_miscdrv->miscdrv_rtc_readtime(&tm);
	if (ret != 0) {
		ALOGE("miscdrv: %s readtime error!\n",__func__);
	}
	#endif
	
	jobject result = env->NewObject(jclassrtctime, jidRtcTime, tm.tm_year, 
	          tm.tm_mon, tm.tm_mday, tm.tm_wday, tm.tm_hour, tm.tm_min, tm.tm_sec); 
	return result;
}

static int android_server_MiscdrvSer_JniSettime(JNIEnv *env, jobject clazz, 
              jint year, jint mon, jint mday, jint wday, jint hour, jint min, jint sec)
{
	ALOGD("miscdrv: %s empty Entry!\n",__func__);
	return 0;
}

static void android_server_MiscdrvSer_JniSetWdClk(JNIEnv *env, jobject clazz, jint val)
{
	ALOGD("miscdrv: %s empty Entry!\n",__func__);
}
#endif

static JNINativeMethod Methods[] = {
	{"miscdrvNativeOpen", "()I", (void*)android_server_MiscdrvSer_JniOpen},
	{"miscdrvNativeDummy", "()V", (void*)android_server_MiscdrvSer_JniDummy},
	{"miscdrvNativeJniLedCtrl", "(IIII)V", (void*)android_server_MiscdrvSer_JniLedCtrl},
	{"miscdrvNativeJniReadtime", "()Landroid/os/RtcTime;", (void*)android_server_MiscdrvSer_JniReadtime},
	{"miscdrvNativeJniSettime", "(IIIIIII)I", (void*)android_server_MiscdrvSer_JniSettime},
	{"miscdrvNativeJniSetWdClk", "(I)V", (void*)android_server_MiscdrvSer_JniSetWdClk},
};
	
int register_android_server_MiscdrvService(JNIEnv* env)
{
	return jniRegisterNativeMethods(env, "com/android/server/MiscdrvService",
															Methods, NELEM(Methods));
}

};
