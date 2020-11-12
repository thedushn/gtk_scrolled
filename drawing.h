//
// Created by dushn on 10.11.20..
//

#ifndef GTK_SCROLLED_WINDOW_DRAWING_H
#define GTK_SCROLLED_WINDOW_DRAWING_H

#include <cairo.h>
#include <gtk/gtk.h>
#define  CPU_NUM 4
int list_num_size;
GtkWidget *window;
GtkWidget *scrolled_window;
GtkWidget *viewport;
GtkAdjustment *adj;
int count;
double value;
cairo_t *t;
typedef struct _Cpu_List Cpu_list;/*!structure for creating linked list for cpu usage */
struct _Cpu_List {

    float     data[CPU_NUM];
    int delay_time;
    Cpu_list *next;
};

/**
 * function do_drawing_cpu(): draws the entire graph, the lines, the frame the seconds and the percentage
 * input:pointer to the graph, pointer to the canvas, step between data, and pointer to the array of cpu usage
 * output:none.
 * */
void do_drawing_cpu2(GtkWidget *widget, cairo_t *cr, guint time_step, Cpu_list *array1) ;
void
draw_graph(cairo_t *cr, int r, double width, double height, double font_size, double time_step, Cpu_list *array);
int cpu_read(Cpu_list **array);
gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,Cpu_list *array);
void draw_percentages(cairo_t *cr, double height, double font_size, double position);
void draw_frame(cairo_t *cr, double width, double height, double font_size, int i);
void writing_seconds(cairo_t *cr, double width, double height, double font_size, int i);
gboolean on_draw_event2(GtkWidget *widget, cairo_t *cr);
void draw_time(cairo_t *cr, int r, double width, double height, double font_size, double time_step, Cpu_list *array);
void draw_lines(cairo_t *cr, double height, double font_size, Cpu_list *array);

#endif //GTK_SCROLLED_WINDOW_DRAWING_H
