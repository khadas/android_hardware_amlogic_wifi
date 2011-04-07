LOCAL_PATH:=$(call my-dir)

ifeq ($(strip $(WIFI_DRIVER)),wgt7310)
file := $(TARGET_OUT)/lib/tiwlan_drv.ko
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/tiwlan_drv.ko | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/wpa_supplicant.conf
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/wpa_supplicant.conf | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/firmware.bin
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/firmware.bin | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/tiwlan_loader
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/tiwlan_loader | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/tiwlan.ini
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/tiwlan.ini | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/wlan_cu
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/wlan_cu | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/wlan_cu_cmd
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/wlan_cu_cmd | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/tiwlan_cali.sh
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/tiwlan_cali.sh | $(ACP)
	$(transform-prebuilt-to-target)
endif
