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
//ralink 
#define RALINK_DRIVER_KO "rt3070sta"

#ifndef WIFI_DRIVER_MODULE_ARG
#define WIFI_DRIVER_MODULE_ARG          ""
#endif

#ifndef WIFI_FIRMWARE_LOADER
#define WIFI_FIRMWARE_LOADER		""
#endif

static const char DRIVER_MODULE_ARG[]   = WIFI_DRIVER_MODULE_ARG;
static const char FIRMWARE_LOADER[]     = WIFI_FIRMWARE_LOADER;
static const char DRIVER_PROP_NAME[]    = "wlan.driver.status";

static struct wifi_vid_pid ralink_vid_pid_tables[] =
{
    {0x148f,0x5370},
    {0x148f,0x5372},
    {0x148f,0x3070},
    {0x0db0,0x3820},
	{0x0db0,0x871c},
	{0x0db0,0x822c},
	{0x0db0,0x871b},
	{0x0db0,0x822b}
};

static int ralink_table_len = sizeof(ralink_vid_pid_tables)/sizeof(struct wifi_vid_pid);
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
int ralink_unload_driver()
{

    if (wifi_rmmod(RALINK_DRIVER_KO) != 0) {
		wpa_printf(MSG_DEBUG, "%s: failed to rmmod RALINK_DRIVER_KO \n", __func__);
    	return -1;
    }
    return 0;
}

int ralink_load_driver()
{
    char mod_path[SYSFS_PATH_MAX];
    snprintf(mod_path, SYSFS_PATH_MAX, "%s/%s.ko",WIFI_DRIVER_MODULE_PATH,RALINK_DRIVER_KO);
    if(wifi_insmod(mod_path, DRIVER_MODULE_ARG) != 0){
		wpa_printf(MSG_DEBUG, "%s: failed to insmod RALINK_DRIVER_KO \n", __func__);
    	return -1;
    }
    return 0;
    
}

int search_ralink(unsigned  short int vid,unsigned short int pid)
{
	int k = 0;
	int count=0;
	for (k = 0;k < ralink_table_len;k++) {
            if (vid == ralink_vid_pid_tables[k].vid && \
                pid == ralink_vid_pid_tables[k].pid) {
				count=1;
            }
        }       
	return count;
}
