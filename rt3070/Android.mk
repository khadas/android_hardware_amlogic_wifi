LOCAL_PATH:=$(call my-dir)

ifeq ($(strip $(WIFI_DRIVER_MODULE_RT3070)),true)
    PRODUCT_COPY_FILES += $(LOCAL_PATH)/rt3070sta.ko:system/lib/rt3070sta.ko
    PRODUCT_COPY_FILES += $(LOCAL_PATH)/wpa_supplicant.conf:root/data/misc/wifi/wpa_supplicant.conf
    PRODUCT_COPY_FILES += $(LOCAL_PATH)/RT2870STA.dat:system/etc/Wireless/RT2870STA/RT2870STA.dat
endif
