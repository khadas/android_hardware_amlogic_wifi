LOCAL_PATH:=$(call my-dir)

ifeq ($(strip $(WIFI_DRIVER)),rtl8192cu)
file := $(TARGET_OUT)/lib/8192cu.ko
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/8192cu.ko | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/wpa_supplicant.conf
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/wpa_supplicant.conf | $(ACP)
	$(transform-prebuilt-to-target)
endif
