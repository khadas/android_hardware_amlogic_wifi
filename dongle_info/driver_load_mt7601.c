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
#define LOG_TAG "MT7601"
#include "cutils/log.h"

static const char MT7601_MODULE_NAME[]  = "mt7601usta";
static const char MT7601_MODULE_TAG[]   = "mt7601usta";
static const char MT7601_MODULE_PATH[]  = "/system/lib/mt7601usta.ko";
static const char MT7601_MODULE_ARG[]   = "";

static const char MTK_MODULE_NAME[]  = "mtprealloc";
static const char MTK_MODULE_TAG[]   = "mtprealloc";
static const char MTK_MODULE_PATH[]  = "/system/lib/mtprealloc.ko";
static const char MTK_MODULE_ARG[]   = "";

#ifndef WIFI_FIRMWARE_LOADER
#define WIFI_FIRMWARE_LOADER		""
#endif

//static const char DRIVER_MODULE_ARG[]   = WIFI_DRIVER_MODULE_ARG;
static const char FIRMWARE_LOADER[]     = WIFI_FIRMWARE_LOADER;
static const char DRIVER_PROP_NAME[]    = "wlan.driver.status";

static struct wifi_vid_pid mt7601_vid_pid_tables[] =
{
    {0x148f,0x7601}
};

static int mt7601_table_len = sizeof(mt7601_vid_pid_tables)/sizeof(struct wifi_vid_pid);

static int wifi_insmod(const char *filename, const char *args)
{
    void *module;
    unsigned int size;
    int ret;

    module = (void*)load_file(filename, &size);
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

static int is_mtprealloc_driver_loaded() {
    FILE *proc;
    char line[sizeof(MTK_MODULE_TAG)+10];

    /*
     * If the property says the driver is loaded, check to
     * make sure that the property setting isn't just left
     * over from a previous manual shutdown or a runtime
     * crash.
     */
    if ((proc = fopen("/proc/modules", "r")) == NULL) {
        ALOGW("Could not open %s", strerror(errno));
        return 0;
    }
    while ((fgets(line, sizeof(line), proc)) != NULL) {
        if (strncmp(line, MTK_MODULE_TAG, strlen(MTK_MODULE_TAG)) == 0) {
            fclose(proc);
            return 1;
        }
    }
    fclose(proc);
    return 0;
}

int mt7601_unload_driver()
{
    if (wifi_rmmod(MT7601_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod mt7601 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod mt7601 driver ! \n");
    return 0;
}

int mt7601_load_driver()
{
    if (!is_mtprealloc_driver_loaded())
       wifi_insmod(MTK_MODULE_PATH, MTK_MODULE_ARG);

    if (wifi_insmod(MT7601_MODULE_PATH, MT7601_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod dhd ! \n");
        return -1;
    }

    ALOGD("Success to insmod mt7601 driver! \n");

    return 0;
}

int search_mt7601(unsigned short int vid,unsigned short int pid)
{
	int k = 0;
	int count=0;

	for (k = 0;k < mt7601_table_len;k++) {
		if (vid == mt7601_vid_pid_tables[k].vid && pid == mt7601_vid_pid_tables[k].pid) {
			count=1;
		}
	}

	return count;
}
