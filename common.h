#ifndef GTK_SCROLLED_WINDOW_COMMON_H
#define GTK_SCROLLED_WINDOW_COMMON_H

#include <pngconf.h>

#define CPU_NUM 4
typedef struct _Cpu_List Cpu_list;/*!structure for creating linked list for cpu usage */
struct _Cpu_List {

    float     data[CPU_NUM];
    int delay_time;
    Cpu_list *next;
};
typedef struct _Network Network;/**structure that contains all the network usage*/
struct __attribute__((__packed__))_Network {

    __uint64_t received_bytes;
    __uint64_t transmited_bytes;
    int delay_time;
    Network *next;


};

#endif