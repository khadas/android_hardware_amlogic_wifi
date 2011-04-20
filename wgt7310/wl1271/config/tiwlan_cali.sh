#!/system/bin/sh

insmod /system/lib/tiwlan_drv.ko 
/system/bin/wlan_loader -i /system/etc/wifi/tiwlan.ini \
                               -f /system/etc/wifi/firmware.bin \
                               -e /data/misc/wifi/nvs_map.bin
ifconfig eth0 up 
/system/bin/wlan_cu -b < /system/etc/wifi/wlan_cu_cmd
rmmod tiwlan_drv
