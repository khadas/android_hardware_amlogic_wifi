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
#	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/realtek/drivers/8189es/rtl8189ES ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
#	cp $(shell pwd)/hardware/wifi/realtek/drivers/8189es/rtl8189ES/8189es.ko $(TARGET_OUT)/
#	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
#	cp $(shell pwd)/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/8189fs.ko $(TARGET_OUT)/
#	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
#	cp $(shell pwd)/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/8188fu.ko $(TARGET_OUT)/
#	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/realtek/drivers/8192eu/rtl8192EU ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
#	cp $(shell pwd)/hardware/wifi/realtek/drivers/8192eu/rtl8192EU/8192eu.ko $(TARGET_OUT)/
#	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/realtek/drivers/8723bs/rtl8723BS ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
#	cp $(shell pwd)/hardware/wifi/realtek/drivers/8723bs/rtl8723BS/8723bs.ko $(TARGET_OUT)/
#	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/realtek/drivers/8723du/rtl8723DU ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
#	cp $(shell pwd)/hardware/wifi/realtek/drivers/8723du/rtl8723DU/8723du.ko $(TARGET_OUT)/
#	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/realtek/drivers/8723ds/rtl8723DS ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
#	cp $(shell pwd)/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/8723ds.ko $(TARGET_OUT)/
#	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/realtek/drivers/8188eu/rtl8xxx_EU ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
#	cp $(shell pwd)/hardware/wifi/realtek/drivers/8188eu/rtl8xxx_EU/8188eu.ko $(TARGET_OUT)/
#	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/realtek/drivers/8812au/rtl8812AU ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
#	cp $(shell pwd)/hardware/wifi/realtek/drivers/8812au/rtl8812AU/8812au.ko $(TARGET_OUT)/
#	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/realtek/drivers/8192es/rtl8192ES ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
#	cp $(shell pwd)/hardware/wifi/realtek/drivers/8192es/rtl8192ES/8192es.ko $(TARGET_OUT)/
#	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/mtk/drivers/mt7601 ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
#	cp $(shell pwd)/hardware/wifi/mtk/drivers/mt7601/mt7601usta.ko $(TARGET_OUT)/
#	cp $(shell pwd)/hardware/wifi/mtk/drivers/mt7601/mtprealloc.ko $(TARGET_OUT)/
#	$(MAKE) ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) LINUX_SRC=$(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ RT28xx_DIR=$(shell pwd)/hardware/wifi/mtk/drivers/mt7603 -f $(shell pwd)/hardware/wifi/mtk/drivers/mt7603/Makefile
#	cp $(shell pwd)/hardware/wifi/mtk/drivers/mt7603/os/linux/mt7603usta.ko $(TARGET_OUT)/
#	$(MAKE)  KERDIR=$(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ  M=$(shell pwd)/hardware/wifi/atbm/atbm602x ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE)
#	$(MAKE) -C $(shell pwd)/$(PRODUCT_OUT)/obj/KERNEL_OBJ M=$(shell pwd)/hardware/wifi/atbm/atbm602x ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
#	cp $(shell pwd)/hardware/wifi/atbm/atbm602x/hal_apollo/atbm602x_usb.ko $(TARGET_OUT)/
#	$(CROSS_COMPILE)strip --strip-debug $(TARGET_OUT)/atbm602x_usb.ko
