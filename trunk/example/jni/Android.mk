LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    		:= SQLite-NDK
LOCAL_LDLIBS			:= -llog -landroid
LOCAL_STATIC_LIBRARIES	:= android_native_app_glue

LOCAL_SRC_FILES := \
	main.cpp \
	sqlite3.c \
	../../sources/sqlite3ndk.cpp

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../../sources
	
include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue) 