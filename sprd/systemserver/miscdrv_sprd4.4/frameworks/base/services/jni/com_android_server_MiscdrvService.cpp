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

#include <stdio.h>

namespace android {

miscdrv_device_t *d_miscdrv;

static jint android_server_MiscdrvSer_JniOpen(JNIEnv *env, jobject clazz)
{
	hw_module_t const* module;
	int err;

	ALOGE("miscdrv: %s Entry!\n",__func__);

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
	ALOGE("miscdrv: %s Entry!\n",__func__);
	
	d_miscdrv->miscdrv_dummy();
}

static JNINativeMethod Methods[] = {
	{"miscdrvNativeOpen", "()I", (void*)android_server_MiscdrvSer_JniOpen},
	{"miscdrvNativeDummy", "()V", (void*)android_server_MiscdrvSer_JniDummy},
};
	
int register_android_server_MiscdrvService(JNIEnv* env)
{
	return jniRegisterNativeMethods(env, "com/android/server/MiscdrvService",
															Methods, NELEM(Methods));
}

};
