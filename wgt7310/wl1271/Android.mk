ifeq ($(WIFI_DRIVER),wl1271)
    BOARD_WLAN_DEVICE := $(WIFI_DRIVER)
    include $(call all-subdir-makefiles)
endif
