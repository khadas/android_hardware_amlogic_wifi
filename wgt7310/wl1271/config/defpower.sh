#!/system/bin/sh

echo "Radio mode on and Default power mode"
echo "/ w p 0 " > /system/etc/wifi/radio.cmd
echo "/ q" >> /system/etc/wifi/radio.cmd

/system/bin/wlan_cu -b < /system/etc/wifi/radio.cmd > /dev/null 2>&1
busybox rm /system/etc/wifi/radio.cmd
