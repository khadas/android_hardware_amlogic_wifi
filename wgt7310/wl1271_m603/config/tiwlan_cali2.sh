#!/system/bin/sh

ifconfig eth0 up 
/system/bin/wlan_cu -b < /system/etc/wifi/wlan_cu_cmd
