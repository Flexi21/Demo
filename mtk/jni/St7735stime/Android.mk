#
# Copyright (C) 2008 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# This makefile shows how to build a shared library and an activity that
# bundles the shared library and calls it using JNI.

TOP_LOCAL_PATH:= $(call my-dir)

# Build activity

LOCAL_PATH:= $(TOP_LOCAL_PATH)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-subdir-java-files)

LOCAL_PACKAGE_NAME := St7735stime

#LOCAL_MODULE := St7735s
LOCAL_STATIC_JAVA_LIBRARIES := libSt7735s

LOCAL_JAVA_LIBRARIES += mediatek-framework telephony-common

#LOCAL_JNI_SHARED_LIBRARIES := libSt7735stime
LOCAL_JNI_SHARED_LIBRARIES := libSt7735s

LOCAL_PROGUARD_ENABLED := disabled

LOCAL_SDK_VERSION := current

#LOCAL_JACK_ENABLED := disabled
# copy lib to /symbol/system/libs
#LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PACKAGE)
#include $(BUILD_STATIC_JAVA_LIBRARY)

##include jar packags part
include $(CLEAR_VARS)
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES := \
    libSt7735s:libs/libSt7735s.jar

include $(BUILD_MULTI_PREBUILT)

# ============================================================

# Also build all of the sub-targets under this one: the shared library.
include $(call all-makefiles-under,$(LOCAL_PATH))

