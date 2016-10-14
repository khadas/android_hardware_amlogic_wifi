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
#define LOG_TAG "QCN9377"
#include "cutils/log.h"


static const char QC9377_MODULE_NAME[]  = "wlan";
static const char QC9377_MODULE_TAG[]   = "wlan";
static const char QC9377_MODULE_PATH[]  = "/system/lib/wlan.ko";
static const char QC9377_MODULE_ARG[]   = "";

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


int qc9377_load_driver()
{
    if (wifi_insmod(QC9377_MODULE_PATH, QC9377_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod qc9377 ! \n");
        return -1;
    }
    ALOGD("Success to insmod qc9377 driver! \n");
    return 0;
}

int qc9377_unload_driver()
{
    if (wifi_rmmod(QC9377_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod qc9377 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod qc9377 driver ! \n");
    return 0;
}

int search_qc9377(unsigned int x,unsigned int y)
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
    if (strstr(sdio_buf,"0701")) {
        ALOGE("Found qc9377 !!!\n");
        return 1;
    }
    return 0;
}
