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

#include "linux_wext.h"
#include "android_drv.h"

#include "common.h"
#include "driver.h"
#include "eloop.h"
#include "priv_netlink.h"
#include "driver_wext.h"
#include "ieee802_11_defs.h"
#include "wpa_common.h"
#include "wpa_ctrl.h"
#include "wpa_supplicant_i.h"
#include "config.h"
#include "linux_ioctl.h"
#include "scan.h"

#include "../../../libhardware_legacy/include/hardware_legacy/wifi.h"
#define ATH6K_DRIVER_KO_1 "compat"
#define ATH6K_DRIVER_KO_2 "cfg80211_ath6kl"
#define ATH6K_DRIVER_KO_3 "ath6kl_usb"

#ifndef WIFI_DRIVER_MODULE_ARG
#define WIFI_DRIVER_MODULE_ARG          ""
#endif

#ifndef WIFI_FIRMWARE_LOADER
#define WIFI_FIRMWARE_LOADER		""
#endif

static const char DRIVER_MODULE_ARG[]   = WIFI_DRIVER_MODULE_ARG;
static const char FIRMWARE_LOADER[]     = WIFI_FIRMWARE_LOADER;
static const char DRIVER_PROP_NAME[]    = "wlan.driver.status";

static struct wifi_vid_pid ath_2_vid_pid_tables[] =
{
    {0x0cf3,0x9374},
    {0x04da,0x3908},
    {0x0cf3,0x1006},
    {0x0cf3,0x7015},
	{0x0cf3,0x7010},	
	{0x0cf3,0x1021},
	{0x0cf3,0x9372},
	{0x1435,0x1220}
};

static int ath_2_table_len = sizeof(ath_2_vid_pid_tables)/sizeof(struct wifi_vid_pid);

//extern int wifi_insmod(const char *filename, const char *args);
//extern int wifi_rmmod(const char *modname);

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
       printf("Unable to unload driver module \"%s\": %s\n",
             modname, strerror(errno));
    return ret;
}

int ath6kl_unload_driver()
{
    if(wifi_rmmod(ATH6K_DRIVER_KO_3) != 0){
    	wpa_printf(MSG_DEBUG, "%s: failed to rmmod ath6kl_usb \n", __func__);
    	return -1;
    }
    
    if(wifi_rmmod(ATH6K_DRIVER_KO_2) != 0){
    	wpa_printf(MSG_DEBUG, "%s: failed to rmmod cfg80211_ath6kl \n", __func__);
    	return -1;
    }
    
    if(wifi_rmmod(ATH6K_DRIVER_KO_1) != 0){
    	wpa_printf(MSG_DEBUG, "%s: failed to rmmod compat \n", __func__);
    	return -1;
    }
 	return 0;
}

//cu8192
int ath6kl_load_driver()
{
    char mod_path[SYSFS_PATH_MAX];
    snprintf(mod_path, SYSFS_PATH_MAX, "%s/%s.ko",WIFI_DRIVER_MODULE_PATH,ATH6K_DRIVER_KO_1);
    if(wifi_insmod(mod_path, DRIVER_MODULE_ARG) != 0){
    	wpa_printf(MSG_DEBUG, "%s: failed to insmod ATH6K_DRIVER_KO_1 \n", __func__);
    	return -1;
    }
	snprintf(mod_path, SYSFS_PATH_MAX, "%s/%s.ko",WIFI_DRIVER_MODULE_PATH,ATH6K_DRIVER_KO_2);
    if(wifi_insmod(mod_path, DRIVER_MODULE_ARG) !=0){
    	wpa_printf(MSG_DEBUG, "%s: failed to insmod ATH6K_DRIVER_KO_2 \n", __func__);
    	return -1;
    }
    
	snprintf(mod_path, SYSFS_PATH_MAX, "%s/%s.ko",WIFI_DRIVER_MODULE_PATH,ATH6K_DRIVER_KO_3);
    if(wifi_insmod(mod_path, DRIVER_MODULE_ARG) != 0){
    	wpa_printf(MSG_DEBUG, "%s: failed to insmod ATH6K_DRIVER_KO_3 \n", __func__);
    	return -1;
    }
    return 0;
}

int search_ath6kl(unsigned  short int vid,unsigned  short int pid)
{
	int k = 0;
	int count=0;
	for (k = 0;k < ath_2_table_len;k++) {
            if (vid == ath_2_vid_pid_tables[k].vid && \
                pid == ath_2_vid_pid_tables[k].pid) {
				count=1;
            }
        }      
	return count;
}
