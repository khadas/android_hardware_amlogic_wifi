#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include "hardware_legacy/wifi.h"
#include "cutils/properties.h"
#include "includes.h"
#include <sys/ioctl.h>
#include <net/if_arp.h>
#include <net/if.h>
#include "dongle_info.h"
#include "linux_wext.h"
#include "android_drv.h"
#include "common.h"
#include "driver.h"
#include "eloop.h"
#include <dlfcn.h>
//#include "priv_netlink.h"
#include "driver_wext.h"
#include "ieee802_11_defs.h"
#include "wpa_common.h"
#include "wpa_ctrl.h"
#include "wpa_supplicant_i.h"
#include "config.h"
#include "linux_ioctl.h"
#include "scan.h"
#define LOG_TAG "RTL8192ES"
#include "cutils/log.h"
#define ES8192_DRIVER_KO "8192es"

#ifndef WIFI_DRIVER_MODULE_ARG
#define WIFI_DRIVER_MODULE_ARG          "ifname=wlan0 if2name=p2p0"
#endif

#ifndef WIFI_FIRMWARE_LOADER
#define WIFI_FIRMWARE_LOADER		""
#endif

static const char DRIVER_MODULE_ARG[]   = WIFI_DRIVER_MODULE_ARG;
static const char FIRMWARE_LOADER[]     = WIFI_FIRMWARE_LOADER;
static const char DRIVER_PROP_NAME[]    = "wlan.driver.status";
extern void set_wifi_type(int type);


void set_usb_sdio_wifi(int type)
{
    void *handle;
    char *error;
    int *usb_sdio_wifi;

    handle = dlopen("/system/lib/libhardware_legacy.so", RTLD_LAZY);
    if (!handle) {
         ALOGD("fail to open libhardware_legacy.so, cannot set usb_sdio_wifi\n");
         return;
    }
    dlerror();
    usb_sdio_wifi = dlsym(handle, "usb_sdio_wifi");

    if (usb_sdio_wifi != NULL)
         *usb_sdio_wifi = type;

    dlclose(handle);
}

static int wifi_insmod(const char *filename, const char *args)
{
    void *module;
    unsigned int size;
    int ret;

    module = load_file(filename, &size);
    if (!module)
        return -1;

    ret = init_module(module, size, args);

    free(module);

    return ret;
}

static int wifi_rmmod(const char *modname)
{
    int ret = -1;
    int maxtry = 10;

    while (maxtry-- > 0) {
        ret = delete_module(modname, O_NONBLOCK | O_EXCL);
        if (ret < 0 && errno == EAGAIN)
            usleep(500000);
        else
            break;
    }

    if (ret != 0)
       ALOGE("Unable to unload driver module \"%s\": %s\n",
             modname, strerror(errno));
    return ret;
}

int es8192_unload_driver()
{
    if (wifi_rmmod(ES8192_DRIVER_KO) != 0) {
        ALOGE("Failed to rmmod rtl8192es driver ! \n");
        return -1;
    }

    ALOGD("Success to rmmod rtl8192es driver! \n");

    return 0;
}

int es8192_load_driver()
{
    char mod_path[SYSFS_PATH_MAX];


	  snprintf(mod_path, SYSFS_PATH_MAX, "%s/%s.ko",WIFI_DRIVER_MODULE_PATH,ES8192_DRIVER_KO);
    if (wifi_insmod(mod_path, DRIVER_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod rtl8192es driver!\n");
        return -1;
    }

    ALOGD("Success to insmod rtl8192es driver! \n");

    return 0;
}


int search_es8192(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    char file_name[] = "/sys/bus/mmc/devices/sdio:0001/sdio:0001:1/device";
    FILE *fp = fopen(file_name,"r");
    if (!fp) {
        ALOGE("Open sdio wifi file failed !!! \n");
        return -1;
    }
    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for %m\n", errno);
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"818b")) {
        ALOGE("Found 8192es !!!\n");
	set_usb_sdio_wifi(1);
        return 1;
    }
    return 0;
}
