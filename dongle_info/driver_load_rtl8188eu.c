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
//#include "priv_netlink.h"
#include "driver_wext.h"
#include "ieee802_11_defs.h"
#include "wpa_common.h"
#include "wpa_ctrl.h"
#include "wpa_supplicant_i.h"
#include "config.h"
#include "linux_ioctl.h"
#include "scan.h"
#define LOG_TAG "RTL8188EU"
#include "cutils/log.h"
#define EU8188_DRIVER_KO "8188eu"
#ifndef WIFI_DRIVER_MODULE_ARG
#define WIFI_DRIVER_MODULE_ARG          "ifname=wlan0 if2name=p2p0"
#endif

#ifndef WIFI_FIRMWARE_LOADER
#define WIFI_FIRMWARE_LOADER		""
#endif

static const char DRIVER_MODULE_ARG[]   = WIFI_DRIVER_MODULE_ARG;
static const char FIRMWARE_LOADER[]     = WIFI_FIRMWARE_LOADER;
static const char DRIVER_PROP_NAME[]    = "wlan.driver.status";

static struct wifi_vid_pid eu8188_vid_pid_tables[] =
{
    {0x0bda,0x8179},
    {0x0bda,0x0179},
    {0x8179,0x07B8}
};

static int eu8188_table_len = sizeof(eu8188_vid_pid_tables)/sizeof(struct wifi_vid_pid);

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

int eu8188_unload_driver()
{
    if (wifi_rmmod(EU8188_DRIVER_KO) != 0) {
        ALOGE("Failed to rmmod rtl8188eu driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod rtl8188eu driver ! \n");
    return 0;
}

int eu8188_load_driver()
{
    char mod_path[SYSFS_PATH_MAX];
    snprintf(mod_path, SYSFS_PATH_MAX, "%s/%s.ko",WIFI_DRIVER_MODULE_PATH,EU8188_DRIVER_KO);
    if (wifi_insmod(mod_path, DRIVER_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod rtl8188eu driver ! \n");
        return -1;
    }

    ALOGD("Success to insmod rtl8188eu driver! \n");

    return 0;
}

int search_8188eu(unsigned short int vid,unsigned short int pid)
{
	int k = 0;
	int count=0;

	ALOGD("Start to search  rtl8188eu driver ...\n");

	for (k = 0;k < eu8188_table_len;k++) {
		if (vid == eu8188_vid_pid_tables[k].vid && pid == eu8188_vid_pid_tables[k].pid) {
			count=1;
		}
	}

	return count;
}
