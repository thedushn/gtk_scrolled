//
// Created by dushn on 26.11.20..
//


#ifndef GTK_SCROLLED_WINDOW_MOUSE_TRACKING_H
#define GTK_SCROLLED_WINDOW_MOUSE_TRACKING_H
#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "drawing.h"
#include "reading.h"
#include <glib.h>
#include <glib/gprintf.h>
#include <inttypes.h>

gboolean motion_notify_event_interrupts(GtkWidget *widget, GdkEventMotion *event);
gboolean motion_notify_event_cpu(GtkWidget *widget, GdkEventMotion *event, Cpu_list *array);
gboolean motion_notify_event_memory(GtkWidget *widget, GdkEventMotion *event, Memory_list *array);
gboolean motion_notify_event_net(GtkWidget *widget, GdkEventMotion *event, Network *array);

#endif //GTK_SCROLLED_WINDOW_MOUSE_TRACKING_H
