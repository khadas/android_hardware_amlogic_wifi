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

#include "wireless_copy.h"
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
//CU8192 
#define CU8192_DRIVER_KO "8192cu"
#define CU8192_DRIVER_KO2 "cfg80211"

#ifndef WIFI_DRIVER_MODULE_ARG
#define WIFI_DRIVER_MODULE_ARG          ""
#endif

#ifndef WIFI_FIRMWARE_LOADER
#define WIFI_FIRMWARE_LOADER		""
#endif

static const char DRIVER_MODULE_ARG[]   = WIFI_DRIVER_MODULE_ARG;
static const char FIRMWARE_LOADER[]     = WIFI_FIRMWARE_LOADER;
static const char DRIVER_PROP_NAME[]    = "wlan.driver.status";

static struct wifi_vid_pid cu8192_vid_pid_tables[] =
{
    {0x2001,0x330a},
    {0x0bda,0x8178},
    {0x0bda,0x8177},
    {0x0bda,0x8176},
    {0x0bda,0x817e},
    {0x0bda,0x018a},
    {0x0b05,0x1791},
    {0x13d3,0x3311},
    {0x13d3,0x3359}
};

static int cu8192_table_len = sizeof(cu8192_vid_pid_tables)/sizeof(struct wifi_vid_pid);

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
int cu8192_unload_driver()
{
    if(wifi_rmmod(CU8192_DRIVER_KO) != 0){
    	printf("failed to rmmod CU8192_DRIVER_KO : \n");
    	wpa_printf(MSG_DEBUG, "%s: failed to rmmod CU8192_DRIVER_KO \n", __func__);
    	return -1;
    }
    
    wifi_rmmod(CU8192_DRIVER_KO2);

    printf("SUCCESS to rmsmod rtl8192cu driver! \n");
    
 	return 0;
}

//cu8192
int cu8192_load_driver()
{
    char mod_path[SYSFS_PATH_MAX];
    
    snprintf(mod_path, SYSFS_PATH_MAX, "%s/%s.ko",WIFI_DRIVER_MODULE_PATH,CU8192_DRIVER_KO2);
    wifi_insmod(mod_path, DRIVER_MODULE_ARG);

	snprintf(mod_path, SYSFS_PATH_MAX, "%s/%s.ko",WIFI_DRIVER_MODULE_PATH,CU8192_DRIVER_KO);
    if(wifi_insmod(mod_path, DRIVER_MODULE_ARG) !=0){
    	printf("failed to insmod CU8192_DRIVER_KO : \n");
    	wpa_printf(MSG_DEBUG, "%s: failed to insmod CU8192_DRIVER_KO \n", __func__);
    	return -1;
    }
    
    printf("SUCCESS to insmod rtl8192cu driver! \n");
    
    return 0;
}

int search_cu(unsigned short int vid,unsigned short int pid)
{
	int k = 0;
	int count=0;
	
	printf("Start to search  rtl8192cu driver\n");
	
	for (k = 0;k < cu8192_table_len;k++) {
        if (vid == cu8192_vid_pid_tables[k].vid && pid == cu8192_vid_pid_tables[k].pid) {
			count=1;
        }
    }
      
	return count;
}
