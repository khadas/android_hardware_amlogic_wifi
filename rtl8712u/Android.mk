LOCAL_PATH:=$(call my-dir)

PRODUCT_COPY_FILES += $(LOCAL_PATH)/8712u.ko:system/lib/8712u.ko
PRODUCT_COPY_FILES += $(LOCAL_PATH)/wpa_supplicant.conf:system/etc/wifi/wpa_supplicant.conf
