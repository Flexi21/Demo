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

#define LOG_TAG "HalgpioService"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>
#include <hardware/hardware.h>
#include <hardware/halgpio.h>
#include <hardware_legacy/vibrator.h>

#include <stdio.h>

namespace android {

halgpio_device_t *halgpio_dev;

static jint android_server_HalGpioService_halGpioOpen(JNIEnv *env, jobject clazz)
{
	hw_module_t const* module;
	int err;

	ALOGE("android_server_HalGpioService_halGpioOpen Entry!\n");

	err = hw_get_module(HALGPIO_HARDWARE_MODULE_ID, &module);
	if (err != 0) {
		ALOGE("Can't get module id HALGPIO_HARDWARE_MODULE_ID, error: %d", err);
		return 0;
	}

	err = module->methods->open(module, HALGPIO_HARDWARE_MODULE_ID,
	(hw_device_t **) &halgpio_dev);
	if (err < 0) {
		ALOGE("Can't open HALGPIO_HARDWARE_MODULE_ID, error: %d", err);
		return 0;
	}

    return reinterpret_cast <jint>(halgpio_dev);
}
	
static jint android_server_HalGpioService_get_gpio_value(JNIEnv *env, jobject clazz, 
																			int gpio_num)
{
	//halgpio_device_t* device = (halgpio_device_t*)ptr;

	ALOGE("android_server_HalGpioService_get_gpio_value\n");
	system("echo 500 > /sys/class/timed_output/vibrator/enable");

	return 0;	
}

static jint android_server_HalGpioService_set_gpio_value(JNIEnv *env,jobject clazz,
																int gpio_num, int value)
{

	return 0;	
}

static jint android_server_HalGpioService_get_gpio_dir(JNIEnv *env,jobject clazz,
																		int gpio_num)
{

	return 0;	
}

static jint android_server_HalGpioService_set_gpio_dir(JNIEnv *env, jobject clazz, 
																int gpio_num, int dir)
{

	return 0;	
}

	
static JNINativeMethod Methods[] = {
	{"halGpioOpen", "()I", (void*)android_server_HalGpioService_halGpioOpen},
	{"halGpioGetValue", "(I)I", (void*)android_server_HalGpioService_get_gpio_value},
	{"halGpioSetValue", "(II)I", (void*)android_server_HalGpioService_set_gpio_value},
	{"halGpioGetDir", "(I)I", (void*)android_server_HalGpioService_get_gpio_dir},
	{"halGpioSetDir", "(II)I", (void*)android_server_HalGpioService_set_gpio_dir},
};
	
int register_android_server_HalgpioService(JNIEnv* env)
{
	return jniRegisterNativeMethods(env, "com/android/server/HalgpioService",
															Methods, NELEM(Methods));
}

};
