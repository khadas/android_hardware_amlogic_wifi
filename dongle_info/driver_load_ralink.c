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
	{0x0db0,0x822b},
	
	{0x148F,0x3071}, /* Ralink 3071 */
	{0x148F,0x3072}, /* Ralink 3072 */
	{0x0DF6,0x003E}, /* Sitecom 3070 */
	{0x0DF6,0x0042}, /* Sitecom 3072 */
	{0x0DF6,0x0048}, /* Sitecom 3070 */
	{0x0DF6,0x0047}, /* Sitecom 3071 */
	{0x0DF6,0x005F}, /* Sitecom 3072 */
	{0x14B2,0x3C12}, /* AL 3070 */
	{0x18C5,0x0012}, /* Corega 3070 */
	{0x083A,0x7511}, /* Arcadyan 3070 */
	{0x083A,0xA701}, /* SMC 3070 */
	{0x083A,0xA702}, /* SMC 3072 */
	{0x1740,0x9703}, /* EnGenius 3070 */
	{0x1740,0x9705}, /* EnGenius 3071 */
	{0x1740,0x9706}, /* EnGenius 3072 */
	{0x1740,0x9707}, /* EnGenius 3070 */
	{0x1740,0x9708}, /* EnGenius 3071 */
	{0x1740,0x9709}, /* EnGenius 3072 */
	{0x13D3,0x3273}, /* AzureWave 3070*/
	{0x13D3,0x3305}, /* AzureWave 3070*/
	{0x1044,0x800D}, /* Gigabyte GN-WB32L 3070 */
	{0x2019,0xAB25}, /* Planex Communications, Inc. RT3070 */
	{0x2019,0x5201}, /* Planex Communications, Inc. RT8070 */
	{0x07B8,0x3070}, /* AboCom 3070 */
	{0x07B8,0x3071}, /* AboCom 3071 */
	{0x07B8,0x3072}, /* Abocom 3072 */
	{0x7392,0x7711}, /* Edimax 3070 */
	{0x7392,0x4085}, /* 2L Central Europe BV 8070 */
	{0x1A32,0x0304}, /* Quanta 3070 */
	{0x1EDA,0x2310}, /* AirTies 3070 */
	{0x07D1,0x3C0A}, /* D-Link 3072 */
	{0x07D1,0x3C0D}, /* D-Link 3070 */
	{0x07D1,0x3C0E}, /* D-Link 3070 */
	{0x07D1,0x3C0F}, /* D-Link 3070 */
	{0x07D1,0x3C16}, /* D-Link 3070 */
	{0x07D1,0x3C17}, /* D-Link 8070 */
	{0x1D4D,0x000C}, /* Pegatron Corporation 3070 */
	{0x1D4D,0x000E}, /* Pegatron Corporation 3070 */
	{0x1D4D,0x0011}, /* Pegatron Corporation 3072 */
	{0x5A57,0x5257}, /* Zinwell 3070 */
	{0x5A57,0x0283}, /* Zinwell 3072 */
	{0x04BB,0x0945}, /* I-O DATA 3072 */
	{0x04BB,0x0947}, /* I-O DATA 3070 */
	{0x04BB,0x0948}, /* I-O DATA 3072 */
	{0x203D,0x1480}, /* Encore 3070 */
	{0x20B8,0x8888}, /* PARA INDUSTRIAL 3070 */
	{0x0B05,0x1784}, /* Asus 3072 */
	{0x203D,0x14A9}, /* Encore 3070*/
	{0x0DB0,0x899A}, /* MSI 3070*/
	{0x0DB0,0x3870}, /* MSI 3070*/
	{0x0DB0,0x870A}, /* MSI 3070*/
	{0x0DB0,0x6899}, /* MSI 3070 */
	{0x0DB0,0x3822}, /* MSI 3070 */
	{0x0DB0,0x3871}, /* MSI 3070 */
	{0x0DB0,0x871A}, /* MSI 3070 */
	{0x0DB0,0x822A}, /* MSI 3070 */
	{0x0DB0,0x3821}, /* Ralink 3070 */
	{0x0DB0,0x821A}, /* Ralink 3070 */
	{0x5A57,0x0282}, /* zintech 3072 */	
	{0x083A,0xA703}, /* IO-MAGIC */
	{0x13D3,0x3307}, /* Azurewave */
	{0x13D3,0x3321}, /* Azurewave */
	{0x07FA,0x7712}, /* Edimax */
	{0x0789,0x0166}, /* Edimax */
	{0x0586,0x341A}, /* Zyxel */
	{0x0586,0x341E}, /* Zyxel */
	{0x0586,0x343E}, /* Zyxel */
	{0x1EDA,0x2012} /* Airties */	
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
