#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>
#include "drawing.h"

GtkWidget *graph;

GtkAdjustment *scrollbar;

Cpu_list *array=NULL;
gboolean scroll_ocured(GtkScrolledWindow *widget,GtkScrollType scrollType, gboolean horizontal,gpointer *gpointer1){

    printf("we are here \n");
    return TRUE;
}
void value_changed(){

    int a=(int)gtk_adjustment_get_value(adj);
     int c=0;
    if(a%30==0){
        return;
    }
 /*   if(a<250){

        if(value<a){
            gtk_adjustment_set_value(adj,30+60);
            value+=30+60;
            return;
        }
        else{
            gtk_adjustment_set_value(adj,0);
            value=0;
            return;
        }
    }*/
    printf("value %.0f \n    a %d\n",value,a);
    if(value<a+30){
        c=a/250;
        value+=60;
        gtk_adjustment_set_value(adj,value);
        gtk_widget_queue_draw(graph);



        return;

    }
    else{
        value-=60;
        gtk_adjustment_set_value(adj,value);
        gtk_widget_queue_draw(graph);

        return;

    }






   printf("page_increment %f\n",gtk_adjustment_get_page_increment(adj));
    printf("page_size %f\n",gtk_adjustment_get_page_size(adj));
    printf("step %f\n",gtk_adjustment_get_step_increment(adj));
    printf("step %f\n",gtk_adjustment_get_step_increment(adj));
    printf("value %f\n",gtk_adjustment_get_value(adj));

}
static void
activate (GtkApplication *app,
          gpointer        user_data)
{
    /* Declare variables */


    GtkWidget *image;

    GtkWidget *grid;

    graph=gtk_drawing_area_new();

    viewport = gtk_viewport_new (NULL,NULL);
    gtk_container_add (GTK_CONTAINER(viewport), graph);
    /* Create a window with a title, and a default size */
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "ScrolledWindow Example");
    gtk_window_set_default_size (GTK_WINDOW (window), 1000, 800);

    /* Create the scrolled window. Usually NULL is passed for both parameters so
     * that it creates the horizontal/vertical adjustments automatically. Setting
     * the scrollbar policy to automatic allows the scrollbars to only show up
     * when needed.
     */
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
   // scrollbar=gtk_scrollbar_new(GTK_ORIENTATION_HORIZONTAL,(GtkAdjustment*)adj);

    /* Set the border width */
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    /* Extract our desired image from a file that we have */
    //image = gtk_image_new_from_file ("slika.png");
    /* And add it to the scrolled window */
  //  gtk_container_add (GTK_CONTAINER (scrolled_window), graph);
   gtk_container_add (GTK_CONTAINER(scrolled_window), viewport);
   // gtk_container_add (GTK_CONTAINER(scrolled_window), graph);
 //   gtk_container_add (GTK_CONTAINER(scrolled_window), scrollbar);
    /* Set the policy of the horizontal and vertical scrollbars to automatic.
     * What this means is that the scrollbars are only present if needed.
     */
//    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
//                                    GTK_POLICY_AUTOMATIC,
//                                    GTK_POLICY_AUTOMATIC);

    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_ALWAYS,
                                    GTK_POLICY_NEVER);
    gtk_widget_set_hexpand(GTK_WIDGET(scrolled_window), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(scrolled_window), TRUE);


    gtk_container_add (GTK_CONTAINER (window), scrolled_window);
    g_signal_connect (G_OBJECT (graph), "draw", G_CALLBACK (on_draw_event), array);

    scrollbar= gtk_scrolled_window_get_hscrollbar(GTK_SCROLLED_WINDOW(scrolled_window));
              adj=  gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(viewport));
//    gtk_adjustment_set_page_increment(adj,2*9*10);
//    gtk_adjustment_set_step_increment(adj,100*10);
//    gtk_adjustment_set_value(adj,9*10);

    g_signal_connect (G_OBJECT (adj), "value_changed", G_CALLBACK (value_changed), NULL);




    gtk_widget_show_all (window);
    gtk_widget_queue_draw(graph);
}



int
main (int argc, char **argv)
{
    gtk_disable_setlocale();
    GtkApplication *app;
    int status;
    list_num_size=0;
    count=0;
    value=0;
    Cpu_list *temp=NULL;
    array=NULL;

    cpu_read(&array);

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    status = g_application_run (G_APPLICATION (app), argc, argv);

    g_object_unref (app);
    while(array){
        temp=array;
        array=array->next;
        free(temp);

    }

    return status;
}
