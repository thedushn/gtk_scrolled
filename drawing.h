//
// Created by dushn on 10.11.20..
//

#ifndef GTK_SCROLLED_WINDOW_DRAWING_H
#define GTK_SCROLLED_WINDOW_DRAWING_H

#include <cairo.h>
#include <gtk/gtk.h>
#include "reading.h"



GtkWidget *window;
GtkWidget *cpu_swindow;
GtkWidget *scrolled_window2;
GtkWidget *scrolled_window3;
GtkWidget *scrolled_window4;
GtkWidget *device_swindow;
GtkWidget *process_swindow;
GtkWidget *viewport;
GtkWidget *viewport2;
GtkWidget *viewport3;
GtkWidget *viewport4;
GtkWidget *viewport5;
GtkAdjustment *adj;
GtkAdjustment *adj2;
GtkAdjustment *adj3;
GtkAdjustment *adj_horizontal;
GtkAdjustment *adj_vertical;

GtkWidget *graph;
GtkWidget *graph2;
GtkWidget *graph3;
GtkWidget *graph4;

double value1;
double value2;
double value3;
double value4;
double value5;
GtkWidget *treeview_devices;
GtkWidget *treeview_tasks;



/**
 * function do_drawing_cpu(): draws the entire graph, the lines, the frame the seconds and the percentage
 * input:pointer to the graph, pointer to the canvas, step between data, and pointer to the array of cpu usage
 * output:none.
 * */
void do_drawing_cpu2(GtkWidget *widget, cairo_t *cr, guint position, Cpu_list *array1, double height, int counter);
void
draw_graph(cairo_t *cr, int r, double height, double font_size, int position, Cpu_list *array, int counter);

gboolean on_draw_event_cpu_mem(GtkWidget *widget, cairo_t *cr, void *array);
void draw_percentages(cairo_t *cr, double height, double font_size, double position, GtkAdjustment *adj_p, int step);
void draw_frame(cairo_t *cr, double width, double height, double font_size, int i);
void writing_seconds(cairo_t *cr, double width, double height, double font_size, int i);
gboolean on_draw_event2(GtkWidget *widget, cairo_t *cr);
void draw_time(cairo_t *cr, double height, double font_size, int x);
void draw_lines(cairo_t *cr, double height, int x, int number_lines, double step, int number_start, int y, bool inter);
void
draw_graph_mem(cairo_t *cr, int r, int font_size, Memory_list *array, double height);
void draw_network_sidebar(cairo_t *cr, double height, double font_size, double position, GtkAdjustment *adj_p,
                          __uint64_t max_number, bool net_int, double position_y, double step);
int position_draw_cpu(Cpu_list **array1, int old_position, int *new_position, int *counter, int step);
int position_draw_net(Network **array1, int old_position, int *new_position, int *counter, __uint64_t *max_number);
void draw_graph_net(cairo_t *cr, int r, double height, double font_size,
                    Network *array, __uint64_t max_number, int counter, int position);
void draw_network_sidebar(cairo_t *cr, double height, double font_size, double position, GtkAdjustment *adj_p,
                          __uint64_t max_number, bool net_int, double position_y, double step);
void
draw_interrupts(cairo_t *cr, double y, double font_size, int x, Interrupts_elements *array, double height,
                int max_number, double step);
#endif //GTK_SCROLLED_WINDOW_DRAWING_H
