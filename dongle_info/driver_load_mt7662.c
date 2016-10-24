#define LOG_TAG "MT7662"
#include "dongle_info.h"
static const char MT7662_MODULE_NAME[]  = "mt7662u_sta";
static const char MT7662_MODULE_TAG[]   = "mt7662u_sta";
static const char MT7662_MODULE_PATH[]  = "/system/lib/mt7662u_sta.ko";
static const char MT7662_MODULE_ARG[]   = "";

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

static struct wifi_vid_pid mt7662_vid_pid_tables[] =
{
    {0x0e8d,0x7662}
};

static int mt7662_table_len = sizeof(mt7662_vid_pid_tables)/sizeof(struct wifi_vid_pid);

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

int mt7662_unload_driver()
{
    if (wifi_rmmod(MT7662_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod mt7662 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod mt7662 driver ! \n");
    return 0;
}

int mt7662_load_driver()
{
    if (!is_mtprealloc_driver_loaded())
       wifi_insmod(MTK_MODULE_PATH, MTK_MODULE_ARG);

    if (wifi_insmod(MT7662_MODULE_PATH, MT7662_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod mt7662 ! \n");
        return -1;
    }

    ALOGD("Success to insmod mt7662 driver! \n");
    return 0;
}

int search_mt7662(unsigned int vid,unsigned int pid)
{
	int k = 0;
	int count=0;

	for (k = 0;k < mt7662_table_len;k++) {
		if (vid == mt7662_vid_pid_tables[k].vid && pid == mt7662_vid_pid_tables[k].pid) {
			count=1;
			write_no("mtk7662");
		}
	}
    write_no("mtk7662");
	return count;
}
