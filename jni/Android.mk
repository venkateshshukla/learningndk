LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS    := -llog
LOCAL_CFLAGS := -DHAVE_INTTYPES_H
LOCAL_MODULE := store
LOCAL_SRC_FILES := com_venky_Store.c Store.c

include $(BUILD_SHARED_LIBRARY)