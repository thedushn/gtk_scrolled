#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "drawing.h"
#include "reading.h"
#include <glib.h>
#include <glib/gprintf.h>

GtkWidget *graph;
GtkWidget *graph2;




Cpu_list *array=NULL;
Network *net_array=NULL;
gboolean
user_function (GtkWidget  *widget,
               int         x,
               int         y,
               gboolean    keyboard_mode,
               GtkTooltip *tooltip,
               gpointer    user_data){

    return true;
};
static gboolean
motion_notify_event( GtkWidget *widget, GdkEventMotion *event )
{
    double x, y;
    double delay=0;
    int a=0;
    Cpu_list *temp=array;

   gchar tesxas[100];
   gchar *s=NULL;


   // printf("hello there \n");
 //   printf("we moved %f %f\n",event->x,event->y);
    if(event->type==GDK_MOTION_NOTIFY){
      //  gtk_widget_set_has_tooltip(window,FALSE);
        x=event->x;
       //  printf("we moved %f %f\n",event->x,event->y);
        if(x<28){
            return TRUE;
        }
        if(fmod(x,30)<=2 && fmod(x,30)>=0 ){
           // printf("hello tooltip\n");
          //  printf("we moved %f %f\n",event->x,event->y);
            if(x<=32){

                g_sprintf (tesxas,"Cpu0 %.2f \nCpu1 %.2f \n"
                        "Cpu2 %.2f \nCpu3 %.2f",0.0,0.0,0.0,0.0);
                gtk_widget_set_tooltip_markup (window,
                                               tesxas);
                s=  gtk_widget_get_tooltip_markup (window);
                printf("%s\n",s);
                return TRUE;
            }

            a=(int)(x/FONT)*INCREMENT;

          ///  printf("which line %d\n",a);
           while(temp->next!=NULL){
                delay+=temp->delay_time;
               if(delay==a){
                   break;
               }
               if(delay>a){
                   return TRUE;
               }
                temp=temp->next;
            }
        //    delay/=250;
         //   delay*=60;
        //    if(((x-delay)<=2 && (x-delay)>=0) ||((x-delay)>=-2 && (x-delay)<=0)){
            g_sprintf (tesxas,"Cpu0 %.2f \nCpu1 %.2f \n"
                    "Cpu2 %.2f \nCpu3 %.2f",temp->data[0],temp->data[1],temp->data[2],temp->data[3]);
          //  gtk_widget_set_has_tooltip(window,TRUE);
            gtk_widget_set_tooltip_markup (window,
                                           tesxas);
          //  s=  gtk_widget_get_tooltip_markup (window);
       // printf("%s\n",s);
          //  gtk_widget_set_has_tooltip(window,TRUE);

            }



      //  }
    }

//    if (event->is_hint)
//        gdk_window_get_device_position (window, ,&x, &y, &state);
//    else
//    {
//        x = event->x;
//        y = event->y;
//        state = event->state;
//    }



    return TRUE;
}
gboolean scroll_ocured(GtkScrolledWindow *widget,GtkScrollType scrollType, gboolean horizontal,gpointer *gpointer1){

    printf("we are here \n");
    return TRUE;
}
void value_changed(){

    int a=(int)gtk_adjustment_get_value(adj);
    int c=0;

    printf("page_increment %f\n",gtk_adjustment_get_page_increment(adj));
  //  printf("window width %d\n",gtk_widget_get_allocated_width(window));
    printf("page_size %f\n",gtk_adjustment_get_page_size(adj));
    printf("step %f\n",gtk_adjustment_get_step_increment(adj));
    printf("step %f\n",gtk_adjustment_get_step_increment(adj));
   // printf("value %f\n",gtk_adjustment_get_value(adj));
    upper= (gtk_adjustment_get_upper(adj)-gtk_adjustment_get_page_size(adj));
    int temp=(int)(gtk_adjustment_get_upper(adj)-gtk_adjustment_get_page_size(adj));
    printf("a %d value %f upper %d \n",a,value,temp);
    c=(int)(a-value);
  //  printf("c %d\n",c);
    if((c)>0){//got bigger

        if(c>FONT){ //bigger then one increment
            if(a==temp){
                printf("here we are\n");
                value=a-FONT;
                gtk_adjustment_set_value(adj,value);
                return;
            }
            c=a/FONT;//clipping
            value=c*FONT;

            gtk_adjustment_set_value(adj,value);
            gtk_widget_queue_draw(graph);
            return;
        }
        else{
            if(a==temp){
                printf("here we are numbero dos\n");
                double temp1;
                int x=a;
                temp1=fmod(a,FONT);
                printf("temp1 %f \n",temp1);
                if(temp1>=FONT/2){
                    x=a/FONT;
                    x=(x*FONT)+60;
                }
                else{
                    x=a/FONT;
                    x=(x*FONT);
                }
                printf("x %d \n",x);
                    value=x;
                gtk_adjustment_set_value(adj,value);
                return;
            }
            value+=FONT;
            gtk_adjustment_set_value(adj,value);
            gtk_widget_queue_draw(graph);
            return;

        }
    }
    else if(c<0){//got smaller
        if(c<-FONT){ //bigger then one increment
            c=a/FONT;//clipping
            value=c*FONT;
            gtk_adjustment_set_value(adj,value);
            gtk_widget_queue_draw(graph);
            return;
        }
        else{
            value-=FONT;
            gtk_adjustment_set_value(adj,value);
            gtk_widget_queue_draw(graph);
            return;

        }


    }
    else{//stayed the same
        gtk_widget_queue_draw(graph);
        return;
    }










}
static void
activate (GtkApplication *app,
          gpointer        user_data)
{
    /* Declare variables */



    GtkWidget *vbox;

    graph=gtk_drawing_area_new();
    graph2=gtk_drawing_area_new();
    GtkWidget *view;
    GtkTextBuffer *buffer;

    GtkWidget* frame1      = gtk_frame_new(NULL);
    GtkWidget* frame2      = gtk_frame_new(NULL);

    view = gtk_text_view_new ();
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL,2);

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    gtk_text_buffer_set_text (buffer, "Hello, this is some text", -1);

    viewport = gtk_viewport_new (NULL,NULL);
    viewport2 = gtk_viewport_new (NULL,NULL);
    gtk_container_add (GTK_CONTAINER(viewport), graph);
    gtk_container_add (GTK_CONTAINER(viewport2), graph2);
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
    scrolled_window2 = gtk_scrolled_window_new (NULL, NULL);
   // scrollbar=gtk_scrollbar_new(GTK_ORIENTATION_HORIZONTAL,(GtkAdjustment*)adj);

    /* Set the border width */
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window2), 10);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window2), 10);
    /* Extract our desired image from a file that we have */
    //image = gtk_image_new_from_file ("slika.png");
    /* And add it to the scrolled window */
   // gtk_container_add (GTK_CONTAINER (scrolled_window), graph);
   gtk_container_add (GTK_CONTAINER(scrolled_window), viewport);
   gtk_container_add (GTK_CONTAINER(scrolled_window2), viewport2);
   // gtk_container_add (GTK_CONTAINER(scrolled_window), graph);
 //   gtk_container_add (GTK_CONTAINER(scrolled_window), scrollbar);
    /* Set the policy of the horizontal and vertical scrollbars to automatic.
     * What this means is that the scrollbars are only present if needed.
     */
//    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
//                                    GTK_POLICY_AUTOMATIC,
//                                    GTK_POLICY_AUTOMATIC);

    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_NEVER);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window2),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_NEVER);
    gtk_widget_set_hexpand(GTK_WIDGET(scrolled_window), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(scrolled_window), TRUE);
    gtk_widget_set_hexpand(GTK_WIDGET(scrolled_window2), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(scrolled_window2), TRUE);

    //gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, FALSE, 0);
   // gtk_container_add (GTK_CONTAINER (vbox), scrolled_window);
  //  gtk_container_add (GTK_CONTAINER (vbox), scrolled_window2);
    gtk_container_add (GTK_CONTAINER (window), scrolled_window);


    g_signal_connect (G_OBJECT (graph), "draw", G_CALLBACK (on_draw_event), array);
    //g_signal_connect (G_OBJECT (graph2), "draw", G_CALLBACK (on_draw_event), array);



              adj=  gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(viewport));
            //  adj=  gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(scrolled_window));
//    gtk_adjustment_set_page_increment(adj,2*9*10);
//    gtk_adjustment_set_step_increment(adj,100*10);
//    gtk_adjustment_set_value(adj,9*10);

    g_signal_connect (G_OBJECT (adj), "value_changed", G_CALLBACK (value_changed), NULL);
    g_signal_connect (G_OBJECT (graph), "motion_notify_event",
                      G_CALLBACK(motion_notify_event), NULL);

    gtk_widget_set_events (graph, GDK_EXPOSURE_MASK
                                         | GDK_LEAVE_NOTIFY_MASK
                                         | GDK_BUTTON_PRESS_MASK
                                         | GDK_POINTER_MOTION_MASK
                                         | GDK_POINTER_MOTION_HINT_MASK);


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
    list_num_size_net=0;
    count=0;
    value=0;
    Cpu_list *temp=NULL;
    Network *temp_net=NULL;
    array=NULL;

   if(!cpu_read(&array)) {
       while(array){
           temp=array;
           array=array->next;
           free(temp);

       }
       array=NULL;
       temp=NULL;
       printf("cpu read erro \n");
       return -1;
   }
//    if(!netw_read(&net_array, &max_number_net)){
//        while(net_array){
//            temp_net=net_array;
//            net_array=net_array->next;
//            free(temp_net);
//
//        }
//        net_array=NULL;
//        temp_net=NULL;
//        while(array){
//            temp=array;
//            array=array->next;
//            free(temp);
//
//        }
//        array=NULL;
//        temp=NULL;
//        printf("network read erro \n");
//        return -1;
//    }


    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    status = g_application_run (G_APPLICATION (app), argc, argv);

    g_object_unref (app);
    while(array){
        temp=array;
        array=array->next;
        free(temp);

    }
    while(net_array){
        temp_net=net_array;
        net_array=net_array->next;
        free(temp_net);

    }
    net_array=NULL;
    temp_net=NULL;

    return status;
}

