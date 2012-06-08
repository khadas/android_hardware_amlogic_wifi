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

#include "driver_cmd_wext.h"


int wpa_driver_wext_driver_cmd(void *priv, char *cmd, char *buf,
					size_t buf_len)
{
	return 0;
}


int wpa_driver_wext_combo_scan(void *priv,struct wpa_driver_scan_params *params)
{
	return 0;
}

int wpa_driver_signal_poll(void *priv, struct wpa_signal_info *si)
{
	return 0;
}
