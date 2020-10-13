LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := uart
LOCAL_SRC_FILES := uart.c

include $(BUILD_EXECUTABLE)
