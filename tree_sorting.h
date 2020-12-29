//
// Created by dushn on 28.12.20..
//


#ifndef GTK_SCROLLED_WINDOW_TREE_SORTING_H
#define GTK_SCROLLED_WINDOW_TREE_SORTING_H

#include "common.h"

#include "string.h"
#include "common.h"
#include <gtk/gtk.h>
#include <stdlib.h>

int task_check(T_Collection *tasks_new, int task_num);

int device_check(Device_List *devices_new, int dev_num);

int refresh_device_data(Device_List *devices_new_list, int dev_num);

int delete_old_devices();

void remove_task_item(gint pid);

void remove_list_item_device(gchar *directory, gchar *name);

void refresh_list_item(Task *task_item);

void refresh_list_item_device(Devices *ref_temp);

int fill_task_item(Task *task_item, GtkTreeIter *iter);

int fill_device_item(Devices *f_temp, GtkTreeIter *iter);


void change_list_store_view_devices(GtkWidget *widget);

void change_list_store_view_process(GtkWidget *widget);

int add_new_task(Task *task_t);

int add_new_dev(Devices *devices);

void create_list_store_task(void);

gint compare_string_list_item(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column);

gint compare_int_list_item_size(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column);

gint compare_int_list_item_time(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column);

gint compare_int_list_item(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column);

void close_window(GtkWidget *widget);

void create_list_store_dev(void);
void test_strtol(int val);

GtkTreeStore *list_tasks; /*liststore for tasks*/
GtkTreeStore *list_devices;

T_Collection *tasks_old;/*!list to the tasks that we keep on client */
Device_List *devices_old_list;
Device_List *devices_new;

GtkWidget *proc_window;

GtkWidget *button_process_task;
GtkWidget *button_process_user;
GtkWidget *button_process_pid;
GtkWidget *button_process_ppid;
GtkWidget *button_process_state;
GtkWidget *button_process_vm_size;
GtkWidget *button_process_rss;
GtkWidget *button_process_cpu;
GtkWidget *button_process_prio;
GtkWidget *button_process_duration;

GtkWidget *button_device_devices;
GtkWidget *button_device_directory;
GtkWidget *button_device_type;
GtkWidget *button_device_avail;
GtkWidget *button_device_used;
GtkWidget *button_device_all;
GtkWidget *button_device_free;
GtkWidget *button_device_total;


enum {/* task column id for sorting and for setting visibility*/
    COL_TASK = 0,
    COL_PID,
    COL_RSS,
    COL_CPU,
    COL_PRIO,
    COL_VSZ,
    COL_PPID,
    COL_STATE,
    COL_UNAME,
    COL_DUR,
    NUM_COLS
};

enum {/*device column id for sorting and for setting visibility*/

    COL_DEV = 0,
    COL_DIR,
    COL_TYPE,
    COL_TOTAL,
    COL_AVAILABLE,
    COL_USED,
    COL_FREE,
    NUM_COLS_DEV


};
#endif //GTK_SCROLLED_WINDOW_TREE_SORTING_H
