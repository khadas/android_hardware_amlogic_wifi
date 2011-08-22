LOCAL_PATH:=$(call my-dir)

ifeq ($(strip $(WIFI_DRIVER)),builtin_wlan0)
file := $(TARGET_OUT)/etc/wifi/wpa_supplicant.conf
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/wpa_supplicant.conf | $(ACP)
	$(transform-prebuilt-to-target)
endif
