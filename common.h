#ifndef GTK_SCROLLED_WINDOW_COMMON_H
#define GTK_SCROLLED_WINDOW_COMMON_H


#include <stdbool.h>
#include <time.h>
#define  CPU_NUM 4
#define FONT 60
#define INCREMENT 250
struct __attribute__((__packed__))tm1 {/*structure that contains information about time used for tasks*/
    __uint32_t tm_sec;            /* Seconds.	[0-60] (1 leap second) */
    __uint32_t tm_min;            /* Minutes.	[0-59] */
    __uint32_t tm_hour;            /* Hours.	[0-23] */
    __uint32_t tm_mday;            /* Day.		[1-31] */
    __uint32_t tm_mon;            /* Month.	[0-11] */
    __uint32_t tm_year;            /* Year	- 1900.  */
    __uint32_t tm_wday;            /* Day of week.	[0-6] */
    __uint32_t tm_yday;            /* Days in year.[0-365]	*/
    __uint32_t tm_isdst;            /* DST.		[-1/0/1]*/

};
typedef struct _Cpu_List Cpu_list;/*!structure for creating linked list for cpu usage */
struct _Cpu_List {

    float     data[CPU_NUM];
    int delay_time;
    Cpu_list *next;
    Cpu_list *prev;
};
typedef struct _Network Network;/**structure that contains all the network usage*/
struct _Network {

    __uint64_t received_bytes;
    __uint64_t transmited_bytes;
    int delay_time;
    Network *next;
    Network *prev;


};
typedef struct _Memory_list Memory_list;/*!structure that contains information about memory usage */

struct  _Memory_list {

    __uint64_t memory_used;
    __uint64_t memory_total;
    char       swap_percentage[16];
    __uint64_t swap_total;
    __uint64_t swap_used;
    char       memory_percentage[16];
    int delay_time;
    Memory_list *next;
    Memory_list *prev;


};

typedef struct _Interrupts Interrupts;
struct __attribute__((__packed__)) _Interrupts {


    char       irq[64];
    char       ime1[64];
    char       ime2[64];
    char       ime3[64];
    char       ime4[64];
    __uint64_t CPU0;
    __uint64_t CPU1;
    __uint64_t CPU2;
    __uint64_t CPU3;




};
typedef struct _Interrupts_elements Interrupts_elements;
struct _Interrupts_elements {

    Interrupts interrupts;
    Interrupts_elements *next;
    Interrupts_elements *prev;

};
typedef struct _Interrupts_List Interrupts_List;
struct _Interrupts_List {

    int delay_time;
    __uint64_t max_number;
    Interrupts_elements *pointer;
    Interrupts_List *next;
    Interrupts_List *prev;
};

typedef struct _Devices Devices;
struct __attribute__((__packed__))_Devices {


    bool       checked;
    __uint64_t used;
    __uint64_t total;
    __uint64_t free;
    __uint64_t avail;
    __uint64_t fid;
    char       name[64];
    char       type[64];
    char       directory[256];
};
typedef struct _Task Task;

struct __attribute__((__packed__)) _Task {
    bool       checked;
    __int16_t  prio;
    __uint32_t uid;
    __uint32_t pid;
    __uint32_t ppid;
    char       cpu_user[16];
    char       cpu_system[16];
    __uint64_t vsz;
    __uint64_t rss;
    __uint64_t start_time;
    struct tm1 stime;
    struct tm1 duration;
    char       state[16];
    char       name[256];
    char       uid_name[256];


};


typedef struct _Device_Collection D_Collection;/*!doubly linked list for devices*/
struct _Device_Collection{

    Devices        devices;
    D_Collection * next;
    D_Collection * prev;
};
typedef struct _Device_List Device_List;
struct _Device_List {

    int delay_time;
    int device_num;
    D_Collection *pointer;
    Device_List *next;
    Device_List *prev;
};
/*!doubly linked list for tasks*/
typedef struct _Task_Collection T_Collection;
struct _Task_Collection{

    Task           task;
    T_Collection * next;
    T_Collection * prev;
};
typedef struct _Task_List Task_List;
struct _Task_List {

    int delay_time;
    int task_num;
    T_Collection *pointer;
    Task_List *next;
    Task_List *prev;
};


int list_num_size;
int list_num_size_net;
int list_num_size_memory;
int list_size_interrupts;
int count;
__uint64_t max_number_net;
Interrupts_List *interrupts_list;

#endif