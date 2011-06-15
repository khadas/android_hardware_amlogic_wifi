ifeq ($(WIFI_DRIVER),wl1271_m603)
    BOARD_WLAN_DEVICE := $(WIFI_DRIVER)
    include $(call all-subdir-makefiles)
endif
