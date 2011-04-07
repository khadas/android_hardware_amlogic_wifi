LOCAL_PATH:=$(call my-dir)

ifeq ($(strip $(WIFI_DRIVER)),rtl8712u)
file := $(TARGET_OUT)/lib/8712u.ko
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/8712cu.ko | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/wpa_supplicant.conf
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/wpa_supplicant.conf | $(ACP)
	$(transform-prebuilt-to-target)
endif
