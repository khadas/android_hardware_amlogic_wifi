#define LOG_TAG "BCM43569"
#include "dongle_info.h"


static const char BCM43569_MODULE_NAME[]  = "bcmdhd";
static const char BCM43569_MODULE_TAG[]   = "bcm43569";
static const char BCM43569_MODULE_PATH[]  = "/system/lib/bcmdhd.ko";
static const char BCM43569_MODULE_ARG[]   = "";

#ifndef WIFI_FIRMWARE_LOADER
#define WIFI_FIRMWARE_LOADER		""
#endif

//static const char DRIVER_MODULE_ARG[]   = WIFI_DRIVER_MODULE_ARG;
static const char FIRMWARE_LOADER[]     = WIFI_FIRMWARE_LOADER;
static const char DRIVER_PROP_NAME[]    = "wlan.driver.status";


static struct wifi_vid_pid bcm43569_vid_pid_tables[] =
{
    {0x0a5c,0x0bdc},
		{0x0a5c,0xbd27}
};

static int bcm43569_table_len = sizeof(bcm43569_vid_pid_tables)/sizeof(struct wifi_vid_pid);



int bcm43569_unload_driver()
{
    if (wifi_rmmod(BCM43569_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bcm43569 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bcm43569 driver ! \n");
    return 0;
}

int bcm43569_load_driver()
{
    if (wifi_insmod(BCM43569_MODULE_PATH, BCM43569_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod bcm43569 driver ! \n");
        return -1;
    }

    ALOGD("Success to insmod bcm43569 driver! \n");

    return 0;
}

int search_bcm43569(unsigned int vid,unsigned int pid)
{
	int k = 0;

	for (k = 0;k < bcm43569_table_len;k++) {
		if (vid == bcm43569_vid_pid_tables[k].vid && pid == bcm43569_vid_pid_tables[k].pid) {
			ALOGD("Success to find bcm43569 pid/vid! \n");
			write_no("bcm43569");
			return 1;
		}
	}
	return 0;
}
