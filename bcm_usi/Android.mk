ifeq ($(WIFI_DRIVER),bcm43341)
    include $(call all-subdir-makefiles)
endif

ifeq ($(WIFI_DRIVER),bcm43241)
    include $(call all-subdir-makefiles)
endif