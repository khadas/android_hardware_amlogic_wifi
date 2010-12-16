LOCAL_PATH:=$(call my-dir)

PRODUCT_COPY_FILES += $(LOCAL_PATH)/8192cu.ko:system/lib/8192cu.ko
PRODUCT_COPY_FILES += $(LOCAL_PATH)/wpa_supplicant.conf:system/etc/wifi/wpa_supplicant.conf
