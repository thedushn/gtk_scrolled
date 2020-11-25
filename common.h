#ifndef GTK_SCROLLED_WINDOW_COMMON_H
#define GTK_SCROLLED_WINDOW_COMMON_H



#define  CPU_NUM 4
#define FONT 60
#define INCREMENT 250
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

int list_num_size;
int list_num_size_net;
int list_num_size_memory;
int list_size_interrupts;
int count;
__uint64_t max_number_net;
Interrupts_List *interrupts_list;

#endif