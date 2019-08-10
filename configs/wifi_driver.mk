KERNEL_ARCH ?= arm64
CROSS_COMPILE ?= aarch64-linux-gnu-
CONFIG_DHD_USE_STATIC_BUF ?= y
PRODUCT_OUT=out/target/product/$(TARGET_PRODUCT)
TARGET_OUT=$(PRODUCT_OUT)/obj/lib_vendor

define bcm-sdio-wifi
	@echo "make bcm sdio wifi driver"
	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.100.10.315.x CONFIG_DHD_USE_STATIC_BUF=y CONFIG_BCMDHD_SDIO=y \
	ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
	cp $(shell pwd)/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.100.10.315.x/dhd.ko $(TARGET_OUT)/
endef

define bcm-usb-wifi
	@echo "make bcm usb wifi driver"
	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.100.10.315.x CONFIG_DHD_USE_STATIC_BUF=y CONFIG_BCMDHD_USB=y \
	ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
	cp $(shell pwd)/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.100.10.315.x/bcmdhd.ko $(TARGET_OUT)/
endef

BCMWIFI:
	@echo "wifi module is bcmwifi"
	$(bcm-sdio-wifi)

AP6181:
	@echo "wifi module is AP6181"
	$(bcm-sdio-wifi)
AP6210:
	@echo "wifi module is AP6210"
	$(bcm-sdio-wifi)
AP6330:
	@echo "wifi module is AP6330"
	$(bcm-sdio-wifi)
AP6234:
	@echo "wifi module is AP6234"
	$(bcm-sdio-wifi)
AP6441:
	@echo "wifi module is AP6441"
	$(bcm-sdio-wifi)
AP6335:
	@echo "wifi module is AP6335"
	$(bcm-sdio-wifi)
AP6212:
	@echo "wifi module is AP6212"
	$(bcm-sdio-wifi)
AP62x2:
	@echo "wifi module is AP62x2"
	$(bcm-sdio-wifi)
AP6255:
	@echo "wifi module is AP6255"
	$(bcm-sdio-wifi)
bcm43341:
	@echo "wifi module is bcm43341"
	$(bcm-sdio-wifi)
bcm43241:
	@echo "wifi module is bcm43241"
	$(bcm-sdio-wifi)
bcm40181:
	@echo "wifi module is bcm40181"
	$(bcm-sdio-wifi)
bcm40183:
	@echo "wifi module is bcm40183"
	$(bcm-sdio-wifi)
bcm4354:
	@echo "wifi module is bcm4354"
	$(bcm-sdio-wifi)
bcm4356:
	@echo "wifi module is bcm4356"
	$(bcm-sdio-wifi)
bcm4358:
	@echo "wifi module is bcm4358"
	$(bcm-sdio-wifi)
bcm43458:
	@echo "wifi module is bcm43458"
	$(bcm-sdio-wifi)
AP6269:
	@echo "wifi module is AP6269"
	$(bcm-usb-wifi)
AP6242:
	@echo "wifi module is AP6242"
	$(bcm-usb-wifi)
AP62x8:
	@echo "wifi module is AP62x8"
	$(bcm-usb-wifi)

multiwifi:
	@echo "make wifi module KERNEL_ARCH is $(KERNEL_ARCH)"
	mkdir -p $(TARGET_OUT)/
	$(bcm-sdio-wifi)
	$(bcm-usb-wifi)
