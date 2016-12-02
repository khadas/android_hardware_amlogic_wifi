/*
 * Copyright 2008, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "QC6174"
#include "dongle_info.h"

static const char QC6174_MODULE_NAME[]  = "wlan";
static const char QC6174_MODULE_TAG[]   = "wlan";
static const char QC6174_MODULE_PATH[]  = "/system/lib/wlan.ko";
static const char QC6174_MODULE_ARG[]   = "";

int qc6174_load_driver()
{
    if (wifi_insmod(QC6174_MODULE_PATH, QC6174_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod qc6174 ! \n");
        return -1;
    }
    ALOGD("Success to insmod qc6174 driver! \n");
    return 0;
}

int qc6174_unload_driver()
{
    if (wifi_rmmod(QC6174_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod qc6174 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod qc6174 driver ! \n");
    return 0;
}

int search_qc6174(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    char file_name[] = "/sys/bus/mmc/devices/sdio:0001/sdio:0001:1/device";
    FILE *fp = fopen(file_name,"r");
    if (!fp)
        return -1;

    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"050a")) {
        write_no("qcn6174");
        ALOGE("Found qc6174 !!!\n");
        return 1;
    }
    return 0;
}
