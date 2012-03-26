ifeq ($(WIFI_DRIVER),bcm40183)
    include $(call all-subdir-makefiles)
endif

ifeq ($(WIFI_DRIVER),bcm40181)
    include $(call all-subdir-makefiles)
endif
