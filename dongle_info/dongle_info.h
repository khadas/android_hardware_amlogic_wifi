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
#include "cutils/misc.h"
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
#include "cutils/log.h"
#include "cutils/misc.h"
#include "private/android_filesystem_config.h"
#ifdef HAVE_LIBC_SYSTEM_PROPERTIES
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#endif
struct wifi_vid_pid {
    unsigned short int vid;
    unsigned short int pid;
};

struct usb_detail_table {
    unsigned  short int usb_port;
    unsigned  short int vid;
    unsigned  short int pid;
};

int write_no(char *wifi_type);
int read_no(char *wifi_type);
extern int init_module(void *, unsigned long, const char *);
extern int delete_module(const char *, unsigned int);
int wifi_insmod(const char *filename, const char *args);
int wifi_rmmod(const char *modname);
int cu8192_load_driver();
int search_cu(unsigned int vid,unsigned int pid);
int cu8192_unload_driver();

int du8192_load_driver();
int search_du(unsigned int vid,unsigned int pid);
int du8192_unload_driver();

int eu8188_load_driver();
int search_8188eu(unsigned int vid,unsigned int pid);
int eu8188_unload_driver();

int au8821_load_driver();
int search_8821au(unsigned int vid,unsigned int pid);
int au8821_unload_driver();

int bu8822_load_driver();
int search_8822bu(unsigned int vid,unsigned int pid);
int bu8822_unload_driver();

int bu8723_load_driver();
int search_8723bu(unsigned int vid,unsigned int pid);
int bu8723_unload_driver();
int ftv8188_load_driver();
int search_8188ftv(unsigned int vid,unsigned int pid);
int ftv8188_unload_driver();

int eu8192_load_driver();
int search_8192eu(unsigned int vid,unsigned int pid);
int eu8192_unload_driver();

int es8192_load_driver();
int search_es8192(unsigned int x,unsigned int y);
int es8192_unload_driver();

int qc9377_load_driver();
int search_qc9377(unsigned int x,unsigned int y);
int qc9377_unload_driver();
int qc6174_load_driver();
int search_qc6174(unsigned int x,unsigned int y);
int qc6174_unload_driver();
int mt7601_load_driver();
int search_mt7601(unsigned int vid,unsigned int pid);
int mt7601_unload_driver();
int mt7603_load_driver();
int search_mt7603(unsigned int vid,unsigned int pid);
int mt7603_unload_driver();
int mt7662_load_driver();
int search_mt7662(unsigned int vid,unsigned int pid);
int mt7662_unload_driver();

int mt7668_load_driver();
int search_mt7668(unsigned int vid,unsigned int pid);
int mt7668_unload_driver();

int bcm43569_load_driver();
int search_bcm43569(unsigned  int vid,unsigned  int pid);
int bcm43569_unload_driver();
