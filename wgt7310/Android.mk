LOCAL_PATH:=$(call my-dir)

ifeq ($(strip $(WIFI_DRIVER_MODULE_WGT7310)),true)
PRODUCT_COPY_FILES += $(LOCAL_PATH)/tiwlan_drv.ko:system/lib/tiwlan_drv.ko
PRODUCT_COPY_FILES += $(LOCAL_PATH)/wpa_supplicant.conf:system/etc/wifi/wpa_supplicant.conf
PRODUCT_COPY_FILES += $(LOCAL_PATH)/firmware.bin:system/etc/wifi/firmware.bin
PRODUCT_COPY_FILES += $(LOCAL_PATH)/tiwlan_loader:system/etc/wifi/tiwlan_loader
PRODUCT_COPY_FILES += $(LOCAL_PATH)/tiwlan.ini:system/etc/wifi/tiwlan.ini
PRODUCT_COPY_FILES += $(LOCAL_PATH)/wlan_cu:system/etc/wifi/wlan_cu
PRODUCT_COPY_FILES += $(LOCAL_PATH)/wlan_cu_cmd:system/etc/wifi/wlan_cu_cmd
PRODUCT_COPY_FILES += $(LOCAL_PATH)/tiwlan_cali.sh:system/etc/wifi/tiwlan_cali.sh
endif
