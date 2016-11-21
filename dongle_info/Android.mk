ifeq ($(MULTI_WIFI_SUPPORT),true)
LOCAL_PATH := $(call my-dir)

L_CFLAGS += -DSYSFS_PATH_MAX=256 -DWIFI_DRIVER_MODULE_PATH=\"\/system\/lib\"

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := lib_driver_load
LOCAL_SHARED_LIBRARIES := libc libcutils
LOCAL_CFLAGS := $(L_CFLAGS)
LOCAL_SRC_FILES := driver_load_rtl8192cu.c \
					driver_load_rtl8192du.c \
					driver_load_rtl8188eu.c \
					driver_load_rtl8188ftv.c \
					driver_load_rtl8821au.c \
					driver_load_rtl8822bu.c \
					driver_load_mt7601.c \
					driver_load_mt7603.c \
					driver_load_mt7662.c \
					driver_load_rtl8192eu.c \
					driver_load_rtl8192es.c \
					driver_load_rtl8723bu.c \
					driver_load_qc9377.c \
					driver_load_qc6174.c \
					driver_load_bcm43569.c
include $(BUILD_SHARED_LIBRARY)
endif
