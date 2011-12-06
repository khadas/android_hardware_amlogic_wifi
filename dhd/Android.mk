ifeq ($(WIFI_DRIVER),dhd)
    include $(call all-subdir-makefiles)
endif
ifeq ($(WIFI_DRIVER),dhd_internal)
    include $(call all-subdir-makefiles)
endif
