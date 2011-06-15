#
# Copyright (C) 2008 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

file := $(TARGET_OUT)/lib/tiwlan_drv.ko
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/tiwlan_drv.ko | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/wpa_supplicant.conf
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/wpa_supplicant.conf | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/firmware.bin
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/firmware.bin | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/tiwlan.ini
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/tiwlan.ini | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/wlan_cu_cmd
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/wlan_cu_cmd | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/tiwlan_cali.sh
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/tiwlan_cali.sh | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/tiwlan_cali2.sh
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/tiwlan_cali2.sh | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/defpower.sh
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/defpower.sh | $(ACP)
	$(transform-prebuilt-to-target)

file := $(TARGET_OUT)/etc/wifi/lowpower.sh
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/lowpower.sh | $(ACP)
	$(transform-prebuilt-to-target)
