#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "drawing.h"
#include "reading.h"
#include <glib.h>
#include <glib/gprintf.h>
#include <inttypes.h>
#include "mouse_tracking.h"
#include "tree_sorting.h"





Cpu_list *cpu_array=NULL;
Network *net_array=NULL;
Memory_list *memory_array=NULL;
void value_changed_horizontal_change(GtkAdjustment *adj_change, int count);
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
            if(a>=temp){

             (*value)=a/FONT;

                ((*value)=((*value)*FONT));
                if(interrupts==false){
                    if(a>temp){
                        (*value)=temp;
                    }
                    value1=value2=value3=(*value);
                    gtk_adjustment_set_value(adj,(*value));
                    gtk_adjustment_set_value(adj2,(*value));
                    gtk_adjustment_set_value(adj3,(*value));
                }
                else{

                    gtk_adjustment_set_value(adj_p,(*value));
                }

                value_changed_horizontal_change(adj_vertical,(int)((*value)/FONT*250));
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
              //  printf("value2 %d\n",(int)value4);
                gtk_adjustment_set_value(adj_p,(*value));
            }
            value_changed_horizontal_change(adj_vertical,(int)((*value)/FONT*250));
            gtk_widget_queue_draw(widget);
            return;
        }
        else{

            if(a>=temp){

                (*value)=a/FONT;


                 ((*value)=((*value)*FONT));


                if(interrupts==false){
                    if(a>temp){
                        (*value)=a;
                    }
                    value1=value2=value3=(*value);
                    gtk_adjustment_set_value(adj,(*value));
                    gtk_adjustment_set_value(adj2,(*value));
                    gtk_adjustment_set_value(adj3,(*value));
                }
                else{
                    (*value)=a;

                    gtk_adjustment_set_value(adj_p,(*value));
                }
                value_changed_horizontal_change(adj_vertical,(int)((*value)/FONT*250));
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
            value_changed_horizontal_change(adj_vertical,(int)((*value)/FONT*250));
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
            value_changed_horizontal_change(adj_vertical,(int)((*value)/FONT*250));
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
            value_changed_horizontal_change(adj_vertical,(int)((*value)/FONT*250));
            gtk_widget_queue_draw(widget);
            return;

        }


    }
    else{//stayed the same
        gtk_widget_queue_draw(widget);
        return;
    }










}

void value_changed_horizontal_change(GtkAdjustment *adj_change, int count){


    Device_List *device_temp=device_list;
    Task_List *task_temp=task_list;
    int delay=0;
    int num=0;
    while(device_temp->next){
        delay+=task_temp->delay_time;
        num++;
        if(delay>count){
            return;
        }
        if(delay==count){
            break;
        }
        task_temp=task_temp->next;
        device_temp=device_temp->next;

    }
    gtk_adjustment_set_value(adj_change,num*gtk_adjustment_get_page_size(adj_change));
    device_check(device_temp,device_temp->device_num);
    task_check(task_temp,task_temp->task_num);

}
void value_changed_vertical_change( GtkAdjustment *adj_change, int count){

    Cpu_list *cpu_list=cpu_array;
    Device_List *device_temp=device_list;
    Task_List *task_temp=task_list;
    int delay=0;

    for(int i=0;i<count;i++){

        delay+=cpu_list->delay_time;
        cpu_list=cpu_list->next;
        device_temp=device_temp->next;
        task_temp=task_temp->next;
    }



    gtk_adjustment_set_value(adj_change,(delay)/INCREMENT*FONT);
    device_check(device_temp,device_temp->device_num);
    task_check(task_temp,task_temp->task_num);




}
void value_changed_vertical( GtkAdjustment *adj_p) {



    int a=(int)gtk_adjustment_get_value(adj_p);
    int c=0;
    double *value;


    GtkWidget *widget=graph4;
    value=&value5;



  int page_size= (int) gtk_adjustment_get_page_size(adj_p);
    int temp=(int)(gtk_adjustment_get_upper(adj_p)-gtk_adjustment_get_page_size(adj_p));

    c=(int)(a-(*value));


    if((c)>0){//got bigger

        if(c>page_size){ //bigger then one increment
            if(a>=temp){
                printf("bigger then one increment %f \n",(*value));
                (*value)=a/page_size;
                value_changed_vertical_change(adj,(int)(*value));
                ((*value)=((*value)*page_size));
                gtk_adjustment_set_value(adj_p,(*value));

                gtk_widget_queue_draw(widget);
                return;
            }
            (*value)=a/page_size;//clipping
            value_changed_vertical_change(adj,(int)(*value));
            (*value)=(*value)*page_size;
            gtk_adjustment_set_value(adj_p,(*value));
            gtk_widget_queue_draw(widget);


            gtk_widget_queue_draw(widget);
            return;
        }
        else{

            if(a>=temp){

                (*value)=a/page_size;

                value_changed_vertical_change(adj,(int)(*value));
                ((*value)=((*value)*page_size));


                 gtk_adjustment_set_value(adj_p,(*value));
                gtk_widget_queue_draw(widget);
                return;
            }

            (*value)+=page_size;

            value_changed_vertical_change(adj,(int) (*value)/page_size);
            gtk_adjustment_set_value(adj_p,(*value));
            gtk_widget_queue_draw(widget);
            return;

        }
    }
    else if(c<0){//got smaller


        if(c<page_size){ //smaller then one increment
            if(a>=temp){

                (*value)=temp-page_size;
                value_changed_vertical_change(adj,(int)(*value)/page_size);
                gtk_adjustment_set_value(adj_p,(*value));
                gtk_widget_queue_draw(widget);
                return;
            }

            (*value)=a/page_size;//clipping
            value_changed_vertical_change(adj,(int)(*value));
            (*value)=(*value)*page_size;
            gtk_adjustment_set_value(adj_p,(*value));
            gtk_widget_queue_draw(widget);
            return;
        }
        else{
            if(a>=temp){

                (*value)=temp-page_size;
                value_changed_vertical_change(adj,(int)(*value)/page_size);
                gtk_adjustment_set_value(adj_p,(*value));
                gtk_widget_queue_draw(widget);
                return;
            }

            (*value)-=page_size;
            value_changed_vertical_change(adj,(int)(*value)/page_size);
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
    hbox2           = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox2, 1, 1, 0);
    graph=gtk_drawing_area_new();
    graph2=gtk_drawing_area_new();
    graph3=gtk_drawing_area_new();
    graph4=gtk_drawing_area_new();

    treeview_devices = gtk_tree_view_new();
    treeview_tasks   = gtk_tree_view_new();

    create_list_store_dev();
    create_list_store_task();

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview_devices), GTK_TREE_MODEL(list_devices));
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(list_devices), 1, GTK_SORT_ASCENDING);

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview_tasks), GTK_TREE_MODEL(list_tasks));
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(list_tasks), 1, GTK_SORT_ASCENDING);
  //  gtk_container_add(GTK_CONTAINER(device_swindow), treeview_devices);


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
    gtk_window_set_title (GTK_WINDOW (window), "System monitor static");
    gtk_window_set_default_size (GTK_WINDOW (window), 1000, 800);

    /* Create the scrolled window. Usually NULL is passed for both parameters so
     * that it creates the horizontal/vertical adjustments automatically. Setting
     * the scrollbar policy to automatic allows the scrollbars to only show up
     * when needed.
     */
    cpu_swindow      = gtk_scrolled_window_new(NULL, NULL);
    scrolled_window2 = gtk_scrolled_window_new(NULL, NULL);
    scrolled_window3 = gtk_scrolled_window_new(NULL, NULL);
    scrolled_window4 = gtk_scrolled_window_new(NULL, NULL);
    device_swindow   = gtk_scrolled_window_new(NULL, NULL);
    process_swindow  = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(device_swindow), treeview_devices);
    gtk_container_add(GTK_CONTAINER(process_swindow), treeview_tasks);

    // scrollbar=gtk_scrollbar_new(GTK_ORIENTATION_HORIZONTAL,(GtkAdjustment*)adj);

    /* Set the border width */
    gtk_container_set_border_width (GTK_CONTAINER (cpu_swindow), 10);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window2), 10);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window3), 10);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window4), 10);
    /* Extract our desired image from a file that we have */
    //image = gtk_image_new_from_file ("slika.png");
    /* And add it to the scrolled window */
   // gtk_container_add (GTK_CONTAINER (cpu_swindow), graph);

//    gtk_container_add(GTK_CONTAINER(frame1), viewport);
//    gtk_container_add(GTK_CONTAINER(frame2), viewport2);
//   gtk_container_add (GTK_CONTAINER(cpu_swindow), frame1);
//
//   gtk_container_add (GTK_CONTAINER(scrolled_window2), frame2);

    gtk_container_add (GTK_CONTAINER(cpu_swindow), viewport);
    gtk_container_add (GTK_CONTAINER(scrolled_window2), viewport2);
    gtk_container_add (GTK_CONTAINER(scrolled_window3), viewport3);
    gtk_container_add (GTK_CONTAINER(scrolled_window4), viewport4);
   // gtk_container_add (GTK_CONTAINER(device_swindow), viewport5);

    ///
   // gtk_container_add (GTK_CONTAINER(cpu_swindow), graph);
 //   gtk_container_add (GTK_CONTAINER(cpu_swindow), scrollbar);
    /* Set the policy of the horizontal and vertical scrollbars to automatic.
     * What this means is that the scrollbars are only present if needed.
     */
//    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (cpu_swindow),
//                                    GTK_POLICY_AUTOMATIC,
//                                    GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(device_swindow),
                                   GTK_POLICY_ALWAYS,
                                   GTK_POLICY_ALWAYS);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(process_swindow),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_ALWAYS);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (cpu_swindow),
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
    gtk_widget_set_hexpand(GTK_WIDGET(cpu_swindow), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(cpu_swindow), TRUE);
    gtk_widget_set_hexpand(GTK_WIDGET(scrolled_window2), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(scrolled_window2), TRUE);
    gtk_widget_set_hexpand(GTK_WIDGET(scrolled_window3), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(scrolled_window3), TRUE);
    gtk_widget_set_hexpand(GTK_WIDGET(scrolled_window4), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(scrolled_window4), TRUE);

    gtk_box_pack_start(GTK_BOX(hbox), cpu_swindow, 0, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), scrolled_window3, 0, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), scrolled_window2, 0, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), scrolled_window4, 0, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), device_swindow, 1, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), process_swindow, 1, TRUE, 1);
    //gtk_box_pack_start(GTK_BOX(vbox), scrolled_window2,0, TRUE, 0);


    //gtk_box_pack_start(GTK_BOX(vbox), cpu_swindow, TRUE, FALSE, 0);
   // gtk_container_add (GTK_CONTAINER (vbox), cpu_swindow);
  //  gtk_container_add (GTK_CONTAINER (vbox), scrolled_window2);
  //  gtk_container_add (GTK_CONTAINER (window), cpu_swindow);
    gtk_container_add (GTK_CONTAINER (window), vbox);


    g_signal_connect (G_OBJECT (graph), "draw", G_CALLBACK(on_draw_event_cpu_mem), cpu_array);
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
    g_signal_connect (G_OBJECT (cpu_swindow), "motion_notify_event",
                      G_CALLBACK(motion_notify_event_cpu), cpu_array);
    g_signal_connect (G_OBJECT (scrolled_window2), "motion_notify_event",
                      G_CALLBACK(motion_notify_event_memory), memory_array);
    g_signal_connect (G_OBJECT (scrolled_window3), "motion_notify_event",
                      G_CALLBACK(motion_notify_event_net), net_array);
    g_signal_connect (G_OBJECT (scrolled_window4), "motion_notify_event",
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


    device_check(device_list,device_list->device_num);
    task_check(task_list,task_list->task_num);

    gtk_widget_show_all (window);

}



int
main (int argc, char **argv)
{
    gtk_disable_setlocale();
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
    Device_List *temp_list_dev=NULL;
    D_Collection *temp_dev=NULL;
    devices_old_list=calloc(1,sizeof(Device_List));
    task_old_list=calloc(1,sizeof(Task_List));
    Task_List *temp_task_list=NULL;
    T_Collection *temp_task=NULL;
   if(task_read(&task_list)) {
       while(task_list){
           temp_task_list=task_list;
           task_list=task_list->next;
           while(temp_task_list->pointer){
               temp_task=temp_task_list->pointer;
               temp_task_list->pointer=temp_task_list->pointer->next;
               free(temp_task);
           }
           free(temp_task_list);

       }
       task_list=NULL;

       printf("interrupts read error \n");
       return -1;
   }

    if(device_read(&device_list)){
        while(device_list){
            temp_list_dev=device_list;
            device_list=device_list->next;
            while(temp_list_dev->pointer){
                temp_dev=temp_list_dev->pointer;
                temp_list_dev->pointer=temp_list_dev->pointer->next;
                free(temp_dev);
            }
            free(temp_list_dev);

        }
        device_list=NULL;

        printf("interrupts read error \n");
        return -1;
    }

    if(interrupts_read(&interrupts_list)){
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


   if(cpu_read(&cpu_array)) {
       while(cpu_array){
           temp=cpu_array;
           cpu_array=cpu_array->next;
           free(temp);

       }
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
       cpu_array=NULL;

       printf("cpu read erro \n");
       return -1;
   }
    if(netw_read(&net_array, &max_number_net)){
        while(net_array){
            temp_net=net_array;
            net_array=net_array->next;
            free(temp_net);

        }
        net_array=NULL;

        while(cpu_array){
            temp=cpu_array;
            cpu_array=cpu_array->next;
            free(temp);

        }
        cpu_array=NULL;
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

        printf("network read erro \n");
        return -1;
    }
   if(memory_read(&memory_array)){
       while(net_array){
           temp_net=net_array;
           net_array=net_array->next;
           free(temp_net);

       }
       net_array=NULL;

       while(cpu_array){
           temp=cpu_array;
           cpu_array=cpu_array->next;
           free(temp);

       }
       cpu_array=NULL;

       while(memory_array){
           temp_mem=memory_array;
           memory_array=memory_array->next;
           free(temp_mem);

       }

       memory_array=NULL;
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

       printf("network read erro \n");
       return -1;
   }


    app = gtk_application_new (NULL, G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);


    status = g_application_run (G_APPLICATION (app), argc, argv);

    g_object_unref (app);

    while(cpu_array){
        temp=cpu_array;
        cpu_array=cpu_array->next;
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

    while(devices_old_list){
        temp_list_dev=devices_old_list;
        devices_old_list=devices_old_list->next;
        while(temp_list_dev->pointer){
            temp_dev=temp_list_dev->pointer;
            temp_list_dev->pointer=temp_list_dev->pointer->next;
            free(temp_dev);
        }
        free(temp_list_dev);

    }
    devices_old_list=NULL;

    while(device_list){
        temp_list_dev=device_list;
        device_list=device_list->next;
        while(temp_list_dev->pointer){
            temp_dev=temp_list_dev->pointer;
            temp_list_dev->pointer=temp_list_dev->pointer->next;
            free(temp_dev);
        }
        free(temp_list_dev);

    }
    device_list=NULL;
    gtk_tree_store_clear(list_devices);

    while(task_list){
        temp_task_list=task_list;
        task_list=task_list->next;
        while(temp_task_list->pointer){
            temp_task=temp_task_list->pointer;
            temp_task_list->pointer=temp_task_list->pointer->next;
            free(temp_task);
        }
        free(temp_task_list);

    }
    task_list=NULL;
    while(task_old_list){
        temp_task_list=task_old_list;
        task_old_list=task_old_list->next;
        while(temp_task_list->pointer){
            temp_task=temp_task_list->pointer;
            temp_task_list->pointer=temp_task_list->pointer->next;
            free(temp_task);
        }
        free(temp_task_list);

    }
    task_old_list=NULL;
    gtk_tree_store_clear(list_tasks);

    return status;
}

