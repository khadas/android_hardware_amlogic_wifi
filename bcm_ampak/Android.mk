ifeq ($(WIFI_DRIVER),bcm40183)
    include $(call all-subdir-makefiles)
endif

ifeq ($(WIFI_DRIVER),bcm40181)
    include $(call all-subdir-makefiles)
endif

ifeq ($(WIFI_DRIVER),AP62x2)
    include $(call all-subdir-makefiles)
endif

ifeq ($(WIFI_DRIVER),AP6335)
    include $(call all-subdir-makefiles)
endif
