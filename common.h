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
};
typedef struct _Network Network;/**structure that contains all the network usage*/
struct __attribute__((__packed__))_Network {

    __uint64_t received_bytes;
    __uint64_t transmited_bytes;
    int delay_time;
    Network *next;


};
int list_num_size;
int list_num_size_net;
int count;
__uint64_t max_number_net;

#endif