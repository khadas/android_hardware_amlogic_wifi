#include "cutils/misc.h"
extern int init_module(void *, unsigned long, const char *);
extern int delete_module(const char *, unsigned int);
struct wifi_vid_pid {
    unsigned short int vid;
    unsigned short int pid;
};

struct usb_detail_table {
    unsigned  short int usb_port;
    unsigned  short int vid;
    unsigned  short int pid;
};
