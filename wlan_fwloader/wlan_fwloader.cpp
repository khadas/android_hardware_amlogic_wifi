/*
 * Copyright (C) 2014 Amlogic, Inc.
 */

#define LOG_TAG "fwloader"

#include <string.h>
#include <net/if_arp.h>
#include <unistd.h>

#include <cutils/log.h>
#include <cutils/properties.h>

/** generic wlan firmware loader that waits for interface to become available */
int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[]) {
    struct ifreq ifr;
    char ifname[PROPERTY_VALUE_MAX];
    int ret = -1;
    int count = 3*(1000/200);   // wait at most 3 seconds

    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        ALOGE("open failed");
        return -1;
    }
    property_get("wifi.interface", ifname, "wlan0");

    memset(&ifr, 0, sizeof(ifr));
    strlcpy(ifr.ifr_name, ifname, IFNAMSIZ);

    while (count-- > 0) {
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
            ret = 0;
            break;
        }
        usleep(200000);
    }
    if (ret == 0) {
        property_set("wlan.driver.status", "ok");
    } else {
        property_set("wlan.driver.status", "failed");
    }
    close(sock);
    return ret;
}
