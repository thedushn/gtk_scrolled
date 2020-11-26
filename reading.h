//
// Created by dushn on 16.11.20..
//

#ifndef GTK_SCROLLED_WINDOW_READING_H
#define GTK_SCROLLED_WINDOW_READING_H


#include <memory.h>
#include "common.h"



int cpu_read(Cpu_list **array);
int netw_read(Network **array, __uint64_t *max_number);
int memory_read(Memory_list **array);
int interrupts_read(Interrupts_List **array);
int interrupt_element_read(Interrupts_List **array,FILE *fp,char buffer_r[512]);
#endif //GTK_SCROLLED_WINDOW_READING_H
