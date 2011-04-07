LOCAL_PATH:=$(call my-dir)

ifeq ($(strip $(WIFI_DRIVER)),dhd)
file := $(TARGET_OUT)/lib/dhd.ko
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/dhd.ko | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/wpa_supplicant.conf
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/wpa_supplicant.conf | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/nvram.txt
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/nvram.txt | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/sdio-g-cdc-full11n-reclaim-roml-wme-idsup.bin
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/sdio-g-cdc-full11n-reclaim-roml-wme-idsup.bin | $(ACP)
	$(transform-prebuilt-to-target)
endif

ifeq ($(strip $(WIFI_DRIVER)),dhd_internal)
file := $(TARGET_OUT)/etc/wifi/wpa_supplicant.conf
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/wpa_supplicant.conf | $(ACP)
	$(transform-prebuilt-to-target)
endif
