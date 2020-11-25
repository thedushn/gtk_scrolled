#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "drawing.h"
#include "reading.h"
#include <glib.h>
#include <glib/gprintf.h>
#include <inttypes.h>


Cpu_list *array=NULL;
Network *net_array=NULL;
Memory_list *memory_array=NULL;

static gboolean
motion_notify_event_net( GtkWidget *widget, GdkEventMotion *event )
{
    double x;
    double delay=0;
    int a=0;
    Network *temp=net_array;

    gchar tesxas[100];





    if(event->type==GDK_MOTION_NOTIFY){

        x=event->x;

        if(x<FONT-2){
            return TRUE;
        }
        if(fmod(x,FONT)<=2 && fmod(x,FONT)>=0 ){

            if(x<=FONT+2){

                g_sprintf (tesxas,"Transmitted %s \n"
                                   "Received %s ",
                           g_format_size_full(0,G_FORMAT_SIZE_IEC_UNITS),
                           g_format_size_full(0,G_FORMAT_SIZE_IEC_UNITS)

                );
                gtk_widget_set_tooltip_markup (window,
                                               tesxas);

                return TRUE;
            }

            a=(int)((x/FONT)-1)*INCREMENT;


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

            g_sprintf (tesxas,"Transmitted %s \n"
                               "Received %s ",
                       g_format_size_full(temp->transmited_bytes,G_FORMAT_SIZE_IEC_UNITS),
                       g_format_size_full(temp->received_bytes,G_FORMAT_SIZE_IEC_UNITS)

            );

            gtk_widget_set_tooltip_markup (window,
                                           tesxas);



        }

    }





    return TRUE;
}
static gboolean motion_notify_event_interrupts(GtkWidget *widget, GdkEventMotion *event){

    int x,y;
    double delay=0;
    int a=0;
    Interrupts_List *temp=interrupts_list;
    Interrupts_elements *temp_elements=NULL;

    gchar tesxas[100];
    if(event->type==GDK_MOTION_NOTIFY){



        if(event->x<FONT){
            return TRUE;
        }
        x=(int)event->x/FONT;
        y=(int)event->y/gtk_widget_get_allocated_height(scrolled_window4);
        if(x>10){
            return TRUE;
        }

        for(int i=0;i<y;i++){
            temp=temp->next;

        }
        temp_elements=temp->pointer;
        for(int i=1;i<x;i++){
            temp_elements=temp_elements->next;

        }

        printf("x %d  y %d \n",x,y);

        g_sprintf (tesxas,"CPU0 %"PRIu64" \nCPU1 %"PRIu64"  \nCPU2 %"PRIu64"  \nCPU3 %"PRIu64" \n %s "
                           ,
                   temp_elements->interrupts.CPU0,
                   temp_elements->interrupts.CPU1,
                   temp_elements->interrupts.CPU2,
                   temp_elements->interrupts.CPU3,
                   temp_elements->interrupts.irq
                   );



           gtk_widget_set_tooltip_markup (window,
                                           tesxas);



        }




    return TRUE;
}

static gboolean
motion_notify_event_memory( GtkWidget *widget, GdkEventMotion *event )
{
    double x;
    double delay=0;
    int a=0;
    Memory_list *temp=memory_array;

    gchar tesxas[100];





    if(event->type==GDK_MOTION_NOTIFY){

        x=event->x;

        if(x<FONT-2){
            return TRUE;
        }
        if(fmod(x,FONT)<=2 && fmod(x,FONT)>=0 ){

            if(x<=FONT+2){

                g_sprintf (tesxas,"Memory_used %s \nMemory_total %s \n"
                                   "Swap_used %s \nSwap_total %s",
                           g_format_size_full(0,G_FORMAT_SIZE_IEC_UNITS),
                           g_format_size_full(temp->memory_total,G_FORMAT_SIZE_IEC_UNITS),
                           g_format_size_full(0,G_FORMAT_SIZE_IEC_UNITS),
                           g_format_size_full(temp->swap_total,G_FORMAT_SIZE_IEC_UNITS)
                );
                gtk_widget_set_tooltip_markup (window,
                                               tesxas);

                return TRUE;
            }

            a=(int)((x/FONT)-1)*INCREMENT;


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

            g_sprintf (tesxas,"Memory_used %s \nMemory_total %s \n"
                    "Swap_used %s \nSwap_total %s",
                       g_format_size_full(temp->memory_used,G_FORMAT_SIZE_IEC_UNITS),
                       g_format_size_full(temp->memory_total,G_FORMAT_SIZE_IEC_UNITS),
                       g_format_size_full(temp->swap_used,G_FORMAT_SIZE_IEC_UNITS),
                       g_format_size_full(temp->swap_total,G_FORMAT_SIZE_IEC_UNITS)
            );

            gtk_widget_set_tooltip_markup (window,
                                           tesxas);



        }

    }





    return TRUE;
}

static gboolean
motion_notify_event_cpu(GtkWidget *widget, GdkEventMotion *event, GtkWidget *window_p)
{
    double x;
    double delay=0;
    int a=0;
    Cpu_list *temp=array;

   gchar tesxas[100];




    if(event->type==GDK_MOTION_NOTIFY){

        x=event->x;

        if(x<FONT-2){
            return TRUE;
        }
        if(fmod(x,FONT)<=2 && fmod(x,FONT)>=0 ){

            if(x<=FONT+2){

                g_sprintf (tesxas,"Cpu0 %.2f \nCpu1 %.2f \n"
                        "Cpu2 %.2f \nCpu3 %.2f",0.0,0.0,0.0,0.0);
                gtk_widget_set_tooltip_markup (window_p,
                                               tesxas);
                printf("%s\n",tesxas);
                return TRUE;
            }

            a=(int)((x/FONT)-1)*INCREMENT;


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

            g_sprintf (tesxas,"Cpu0 %.2f \nCpu1 %.2f \n"
                    "Cpu2 %.2f \nCpu3 %.2f",temp->data[0],temp->data[1],temp->data[2],temp->data[3]);

            gtk_widget_set_tooltip_markup (window_p,
                                           tesxas);
            printf("%s\n",tesxas);


            }




    }





    return TRUE;
}

void value_changed( GtkAdjustment *adj_p) {

    int a=(int)gtk_adjustment_get_value(adj_p);
    int c=0;
    double *value;
    bool interrupts=false;


    GtkWidget *widget;
    if(adj_p==adj){
        value=&value1;

        widget=graph;
    }else if(adj_p==adj2){
        value=&value2;
        widget=graph2;

    }
    else if(adj_p==adj3){
        value=&value3;
        widget=graph3;

    }else{
        value=&value4;
        widget=graph4;
        interrupts=true;
    }



    int temp=(int)(gtk_adjustment_get_upper(adj_p)-gtk_adjustment_get_page_size(adj_p));
 //   printf("a %d value %f upper %d \n",a,*value,temp);
    c=(int)(a-(*value));


    if((c)>0){//got bigger

        if(c>FONT){ //bigger then one increment
            if(a==temp){

             (*value)=a/FONT;

                ((*value)=((*value)*FONT));
                if(interrupts==false){
                    value1=value2=value3=(*value);
                    gtk_adjustment_set_value(adj,(*value));
                    gtk_adjustment_set_value(adj2,(*value));
                    gtk_adjustment_set_value(adj3,(*value));
                }
                else{
                    gtk_adjustment_set_value(adj_p,(*value));
                }


                gtk_widget_queue_draw(widget);
                return;
            }
            c=a/FONT;//clipping
            (*value)=c*FONT;

            if(interrupts==false){
                value1=value2=value3=(*value);
                gtk_adjustment_set_value(adj,(*value));
                gtk_adjustment_set_value(adj2,(*value));
                gtk_adjustment_set_value(adj3,(*value));
            }
            else{
                gtk_adjustment_set_value(adj_p,(*value));
            }
            gtk_widget_queue_draw(widget);
            return;
        }
        else{

            if(a==temp){

                (*value)=a/FONT;


                 ((*value)=((*value)*FONT));


                if(interrupts==false){
                    value1=value2=value3=(*value);
                    gtk_adjustment_set_value(adj,(*value));
                    gtk_adjustment_set_value(adj2,(*value));
                    gtk_adjustment_set_value(adj3,(*value));
                }
                else{
                    gtk_adjustment_set_value(adj_p,(*value));
                }
                gtk_widget_queue_draw(widget);
                return;
            }
            (*value)+=FONT;
            if(interrupts==false){
                value1=value2=value3=(*value);
                gtk_adjustment_set_value(adj,(*value));
                gtk_adjustment_set_value(adj2,(*value));
                gtk_adjustment_set_value(adj3,(*value));
            }
            else{
                gtk_adjustment_set_value(adj_p,(*value));
            }
            gtk_widget_queue_draw(widget);
            return;

        }
    }
    else if(c<0){//got smaller
        if(c<-FONT){ //bigger then one increment
            c=a/FONT;//clipping
            (*value)=c*FONT;
            if(interrupts==false){
                value1=value2=value3=(*value);
                gtk_adjustment_set_value(adj,(*value));
                gtk_adjustment_set_value(adj2,(*value));
                gtk_adjustment_set_value(adj3,(*value));
            }
            else{
                gtk_adjustment_set_value(adj_p,(*value));
            }
            gtk_widget_queue_draw(widget);
            return;
        }
        else{
            (*value)-=FONT;
            if(interrupts==false){
                value1=value2=value3=(*value);
                gtk_adjustment_set_value(adj,(*value));
                gtk_adjustment_set_value(adj2,(*value));
                gtk_adjustment_set_value(adj3,(*value));
            }
            else{
                gtk_adjustment_set_value(adj_p,(*value));
            }
            gtk_widget_queue_draw(widget);
            return;

        }


    }
    else{//stayed the same
        gtk_widget_queue_draw(widget);
        return;
    }










}

void value_changed_vertical( GtkAdjustment *adj_p) {

    int a=(int)gtk_adjustment_get_value(adj_p);
    int c=0;
    double *value;


    GtkWidget *widget=graph4;
    value=&value5;



  int page_size= (int) gtk_adjustment_get_page_size(adj_p);
    int temp=(int)(gtk_adjustment_get_upper(adj_p)-gtk_adjustment_get_page_size(adj_p));
    printf("a %d value %f upper %d page_size %d \n",a,*value,temp,page_size);
    c=(int)(a-(*value));


    if((c)>0){//got bigger

        if(c>page_size){ //bigger then one increment
            if(a==temp){

                (*value)=a/page_size;

                ((*value)=((*value)*page_size));
                gtk_adjustment_set_value(adj_p,(*value));

                gtk_widget_queue_draw(widget);
                return;
            }
            c=a/page_size;//clipping
            (*value)=c*page_size;


            gtk_widget_queue_draw(widget);
            return;
        }
        else{

            if(a==temp){

                (*value)=a/page_size;


                ((*value)=((*value)*page_size));


                 gtk_adjustment_set_value(adj_p,(*value));
                gtk_widget_queue_draw(widget);
                return;
            }

            (*value)+=page_size;
            gtk_adjustment_set_value(adj_p,(*value));
            gtk_widget_queue_draw(widget);
            return;

        }
    }
    else if(c<0){//got smaller
        if(c<-page_size){ //bigger then one increment
            c=a/page_size;//clipping
            (*value)=c*page_size;
            gtk_adjustment_set_value(adj_p,(*value));
            gtk_widget_queue_draw(widget);
            return;
        }
        else{
            (*value)-=page_size;

            gtk_adjustment_set_value(adj_p,(*value));
            gtk_widget_queue_draw(widget);
            return;

        }


    }
    else{//stayed the same
        gtk_widget_queue_draw(widget);
        return;
    }










}
static void
activate (GtkApplication *app,
          gpointer        user_data)
{
    /* Declare variables */



    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *hbox2;
    vbox            = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    hbox            = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    hbox2            = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox2, 1, 1, 0);
    graph=gtk_drawing_area_new();
    graph2=gtk_drawing_area_new();
    graph3=gtk_drawing_area_new();
    graph4=gtk_drawing_area_new();





    viewport = gtk_viewport_new (NULL,NULL);
    viewport2 = gtk_viewport_new (NULL,NULL);
    viewport3 = gtk_viewport_new (NULL,NULL);
    viewport4 = gtk_viewport_new (NULL,NULL);

    gtk_container_add (GTK_CONTAINER(viewport), graph);

    gtk_container_add (GTK_CONTAINER(viewport2), graph2);

    gtk_container_add (GTK_CONTAINER(viewport3), graph3);
    gtk_container_add (GTK_CONTAINER(viewport4), graph4);







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
    scrolled_window3 = gtk_scrolled_window_new (NULL, NULL);
    scrolled_window4 = gtk_scrolled_window_new (NULL, NULL);
   // scrollbar=gtk_scrollbar_new(GTK_ORIENTATION_HORIZONTAL,(GtkAdjustment*)adj);

    /* Set the border width */
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window2), 10);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window3), 10);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window4), 10);
    /* Extract our desired image from a file that we have */
    //image = gtk_image_new_from_file ("slika.png");
    /* And add it to the scrolled window */
   // gtk_container_add (GTK_CONTAINER (scrolled_window), graph);

//    gtk_container_add(GTK_CONTAINER(frame1), viewport);
//    gtk_container_add(GTK_CONTAINER(frame2), viewport2);
//   gtk_container_add (GTK_CONTAINER(scrolled_window), frame1);
//
//   gtk_container_add (GTK_CONTAINER(scrolled_window2), frame2);

    gtk_container_add (GTK_CONTAINER(scrolled_window), viewport);
    gtk_container_add (GTK_CONTAINER(scrolled_window2), viewport2);
    gtk_container_add (GTK_CONTAINER(scrolled_window3), viewport3);
    gtk_container_add (GTK_CONTAINER(scrolled_window4), viewport4);

    ///
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
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window3),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_NEVER);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window4),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    gtk_widget_set_hexpand(GTK_WIDGET(scrolled_window), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(scrolled_window), TRUE);
    gtk_widget_set_hexpand(GTK_WIDGET(scrolled_window2), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(scrolled_window2), TRUE);
    gtk_widget_set_hexpand(GTK_WIDGET(scrolled_window3), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(scrolled_window3), TRUE);
    gtk_widget_set_hexpand(GTK_WIDGET(scrolled_window4), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(scrolled_window4), TRUE);

    gtk_box_pack_start(GTK_BOX(hbox), scrolled_window, 0, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), scrolled_window3, 0, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), scrolled_window2, 0, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), scrolled_window4, 0, TRUE, 0);
    //gtk_box_pack_start(GTK_BOX(vbox), scrolled_window2,0, TRUE, 0);


    //gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, FALSE, 0);
   // gtk_container_add (GTK_CONTAINER (vbox), scrolled_window);
  //  gtk_container_add (GTK_CONTAINER (vbox), scrolled_window2);
  //  gtk_container_add (GTK_CONTAINER (window), scrolled_window);
    gtk_container_add (GTK_CONTAINER (window), vbox);


    g_signal_connect (G_OBJECT (graph), "draw", G_CALLBACK(on_draw_event_cpu_mem), array);
    g_signal_connect (G_OBJECT (graph2), "draw", G_CALLBACK(on_draw_event_cpu_mem), memory_array);
    g_signal_connect (G_OBJECT (graph3), "draw", G_CALLBACK(on_draw_event_cpu_mem), net_array);
    g_signal_connect (G_OBJECT (graph4), "draw", G_CALLBACK(on_draw_event_cpu_mem), interrupts_list);



              adj            =  gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(viewport));
              adj2           =  gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(viewport2));
              adj3           =  gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(viewport3));
              adj_horizontal =  gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(viewport4));
              adj_vertical   =  gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(viewport4));


    g_signal_connect (G_OBJECT (adj), "value_changed", G_CALLBACK(value_changed),NULL);
    g_signal_connect (G_OBJECT (adj2), "value_changed", G_CALLBACK(value_changed),NULL);
    g_signal_connect (G_OBJECT (adj3), "value_changed", G_CALLBACK(value_changed),NULL);
    g_signal_connect (G_OBJECT (adj_horizontal), "value_changed", G_CALLBACK(value_changed),NULL);
    g_signal_connect (G_OBJECT (adj_vertical), "value_changed", G_CALLBACK(value_changed_vertical),NULL);
    g_signal_connect (G_OBJECT (graph), "motion_notify_event",
                      G_CALLBACK(motion_notify_event_cpu), scrolled_window);
    g_signal_connect (G_OBJECT (graph2), "motion_notify_event",
                      G_CALLBACK(motion_notify_event_memory), NULL);
    g_signal_connect (G_OBJECT (graph3), "motion_notify_event",
                      G_CALLBACK(motion_notify_event_net), NULL);
    g_signal_connect (G_OBJECT (graph4), "motion_notify_event",
                      G_CALLBACK(motion_notify_event_interrupts), NULL);

    gtk_widget_set_events (graph, GDK_EXPOSURE_MASK
                                         | GDK_LEAVE_NOTIFY_MASK
                                         | GDK_BUTTON_PRESS_MASK
                                         | GDK_POINTER_MOTION_MASK
                                         | GDK_POINTER_MOTION_HINT_MASK);
    gtk_widget_set_events (graph2, GDK_EXPOSURE_MASK
                                  | GDK_LEAVE_NOTIFY_MASK
                                  | GDK_BUTTON_PRESS_MASK
                                  | GDK_POINTER_MOTION_MASK
                                  | GDK_POINTER_MOTION_HINT_MASK);
    gtk_widget_set_events (graph3, GDK_EXPOSURE_MASK
                                   | GDK_LEAVE_NOTIFY_MASK
                                   | GDK_BUTTON_PRESS_MASK
                                   | GDK_POINTER_MOTION_MASK
                                   | GDK_POINTER_MOTION_HINT_MASK);
    gtk_widget_set_events (graph4, GDK_EXPOSURE_MASK
                                   | GDK_LEAVE_NOTIFY_MASK
                                   | GDK_BUTTON_PRESS_MASK
                                   | GDK_POINTER_MOTION_MASK
                                   | GDK_POINTER_MOTION_HINT_MASK);


    gtk_widget_show_all (window);

}



int
main (int argc, char **argv)
{
  //  gtk_disable_setlocale();
    GtkApplication *app;
    int status;
    list_num_size=0;
    list_num_size_net=0;
    list_size_interrupts=0;
    count=0;
    value1=0;
    value2=0;
    value3=0;
    value4=0;
    value5=0;
    Cpu_list *temp=NULL;
    Network *temp_net=NULL;
    Memory_list *temp_mem=NULL;
    interrupts_list=NULL;
    Interrupts_List *temp_list_int=NULL;
    Interrupts_elements *temp_intrp=NULL;
    array=NULL;
    if(!interrupts_read(&interrupts_list)){
        while(interrupts_list){
            temp_list_int=interrupts_list;
            interrupts_list=interrupts_list->next;
            while(temp_list_int->pointer){
                temp_intrp=temp_list_int->pointer;
                temp_list_int->pointer=temp_list_int->pointer->next;
               free(temp_intrp);
            }
            free(temp_list_int);

        }
        interrupts_list=NULL;

        printf("interrupts read error \n");
        return -1;
    }

   if(!cpu_read(&array)) {
       while(array){
           temp=array;
           array=array->next;
           free(temp);

       }
       array=NULL;

       printf("cpu read erro \n");
       return -1;
   }
    if(!netw_read(&net_array, &max_number_net)){
        while(net_array){
            temp_net=net_array;
            net_array=net_array->next;
            free(temp_net);

        }
        net_array=NULL;

        while(array){
            temp=array;
            array=array->next;
            free(temp);

        }
        array=NULL;

        printf("network read erro \n");
        return -1;
    }
   if(!memory_read(&memory_array)){
       while(net_array){
           temp_net=net_array;
           net_array=net_array->next;
           free(temp_net);

       }
       net_array=NULL;

       while(array){
           temp=array;
           array=array->next;
           free(temp);

       }
       array=NULL;

       while(memory_array){
           temp_mem=memory_array;
           memory_array=memory_array->next;
           free(temp_mem);

       }
       memory_array=NULL;

       printf("network read erro \n");
       return -1;
   }


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
    while(memory_array){
        temp_mem=memory_array;
        memory_array=memory_array->next;
        free(temp_mem);

    }
    memory_array=NULL;
    net_array=NULL;
    while(interrupts_list){
        temp_list_int=interrupts_list;
        interrupts_list=interrupts_list->next;
        while(temp_list_int->pointer){
            temp_intrp=temp_list_int->pointer;
            temp_list_int->pointer=temp_list_int->pointer->next;
            free(temp_intrp);
        }
        free(temp_list_int);

    }
    interrupts_list=NULL;


    return status;
}

