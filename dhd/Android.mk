LOCAL_PATH:=$(call my-dir)

#ifeq ($(strip $(WIFI_DRIVER_MODULE_DHD)),true)
#    PRODUCT_COPY_FILES += $(LOCAL_PATH)/dhd.ko:system/lib/dhd.ko
#    PRODUCT_COPY_FILES += $(LOCAL_PATH)/wpa_supplicant.conf:root/data/misc/wifi/wpa_supplicant.conf
#    PRODUCT_COPY_FILES += $(LOCAL_PATH)/nvram.txt:system/etc/nvram.txt
#    PRODUCT_COPY_FILES += $(LOCAL_PATH)/sdio-g-cdc-full11n-reclaim-roml-wme-idsup.bin:system/etc/sdio-g-cdc-full11n-reclaim-roml-wme-idsup.bin
#endif

# change location of wpa_supplicant.conf from /data/misc/wifi/ to /system/etc/
# /data/misc/wifi/wpa_supplicant.conf is a copy from /data/misc/wifi/wpa_supplicant.conf, it would be cleaned if user do factory reset
# See hardware/libhardware_legacy/wifi/wifi.c for more infomation, frank.chen
# And use ALL_PREBUILT to copy files, it make sure files can be copy everytime.

ifeq ($(strip $(WIFI_DRIVER_MODULE_DHD)),true)
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
