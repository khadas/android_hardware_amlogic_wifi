LOCAL_PATH:=$(call my-dir)

ifeq ($(strip $(WIFI_DRIVER_MODULE_DHD)),true)
    PRODUCT_COPY_FILES += $(LOCAL_PATH)/dhd.ko:system/lib/dhd.ko
    PRODUCT_COPY_FILES += $(LOCAL_PATH)/wpa_supplicant.conf:root/data/misc/wifi/wpa_supplicant.conf
    PRODUCT_COPY_FILES += $(LOCAL_PATH)/nvram.txt:system/etc/nvram.txt
    PRODUCT_COPY_FILES += $(LOCAL_PATH)/sdio-g-cdc-full11n-reclaim-roml-wme-idsup.bin:system/etc/sdio-g-cdc-full11n-reclaim-roml-wme-idsup.bin
endif
