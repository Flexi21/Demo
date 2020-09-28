LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES += vendor/sprd/modules/libatci
#engineermode invoke native lib
LOCAL_STATIC_LIBRARIES += libatci

LOCAL_SRC_FILES:= atset.cpp
LOCAL_MODULE := atset
LOCAL_SHARED_LIBRARIES := libcutils libutils liblog libbinder librilutils libandroid_runtime
LOCAL_SHARED_LIBRARIES += libefuse
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)
