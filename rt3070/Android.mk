LOCAL_PATH:=$(call my-dir)

ifeq ($(strip $(WIFI_DRIVER)),rt3070)
file := $(TARGET_OUT)/lib/rt3070sta.ko
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/rt3070sta.ko | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/wpa_supplicant.conf
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/wpa_supplicant.conf | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/Wireless/RT2870STA/RT2870STA.dat
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/RT2870STA.dat | $(ACP)
	$(transform-prebuilt-to-target)
endif
