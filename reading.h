//
// Created by dushn on 16.11.20..
//

#ifndef GTK_SCROLLED_WINDOW_READING_H
#define GTK_SCROLLED_WINDOW_READING_H


#include <memory.h>
#include "common.h"



int cpu_read(Cpu_list **array);
int netw_read(Network **array, __uint64_t *max_number);
#endif //GTK_SCROLLED_WINDOW_READING_H
