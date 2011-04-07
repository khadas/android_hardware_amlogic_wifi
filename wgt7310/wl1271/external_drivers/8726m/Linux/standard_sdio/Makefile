

#APPCFLAGS += -O2 -I. -Wall -Wstrict-prototypes -Wno-comment -D_GNU_SOURCE 

#ifeq "$(DV_KERNEL_BASELINE_IS)" "baseline1"
#EXTRA_CFLAGS += -DTI_KERNEL_BASELINE1
#else
#EXTRA_CFLAGS += -DTI_KERNEL_BASELINE2
#endif

ifneq ($(KERNELRELEASE),)
# kernel build system and can use its language.
# driver specific flags contain:
# -DSSD_DEBUG         enables debugging code and maskable debug messages
# -DSSD_REPORT_LEVEL=n              report level to the debug console
# -DLEGACY_SDIO_ONLY                for future use - ignored in this implementation
# -DLEGACY_SD_ONLY                for future use - ignored in this implementation
# -DFULL_SHARED_SDIO_FRAMEWORK                for future use - ignored in this implementation
# -DBUS_GUARD_SCHED_RR                for future use - ignored in this implementation
# -DBUS_GUARD_SCHED_PRI                for future use - ignored in this implementation
# -DBUS_GUARD_SCHED_FIFO                for future use - ignored in this implementation
# -DSDIO_ADAPTER_TI                for future use - ignored in this implementation
# -DSDIO_HW_SELECTOR_SDIO_SINGLE_DEVICE                for future use - ignored in this implementation


#EXTRA_CFLAGS += -DSSD_DEBUG -DSSD_REPORTLEVEL=4
#EXTRA_CFLAGS += -DTIWLAN_CLT_LEVEL=0 
# Otherwise we were called directly from the command
# line; invoke the kernel build system.
#obj-m := ssd.o ssd_testdrv.o TestDrv.o
obj-m := SdioDrv.o
#obj-m := tisdio.o
#ssd-objs := davinci_sdiodrv.o ssd_debug.o ssd_adapter.o ssd_manager.o ssd_busguard.o ssd_sd.o host_platform.o

else
KERNEL_DIR ?= /home/mark/Project/Mike_Driver/esi-kernel-src/
PWD := $(shell pwd)
all:
	$(MAKE) CROSS_COMPILE=$(CROSS_COMPILE) ARCH=$(ARCH) -C $(KERNEL_DIR) M=$(PWD) modules
#	obj-m := tisdio.o
endif

clean:
	rm -f *.o *~ *.~* core .depend dep $(SRCS_OBJ)
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions

