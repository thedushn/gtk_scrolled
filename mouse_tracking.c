//
// Created by dushn on 26.11.20..
//

#include "mouse_tracking.h"

 gboolean motion_notify_event_interrupts(GtkWidget *widget, GdkEventMotion *event){

    int x,y;
    double prep;
     int delay=0;
     adj_vertical   =  gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(viewport4));
     adj_horizontal =  gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(viewport4));
    Interrupts_List *temp=interrupts_list;
    Interrupts_elements *temp_elements=NULL;

    gchar tesxas[100];
     if(event->type==GDK_BUTTON_PRESS_MASK){
         return FALSE;
     }
    if(event->type==GDK_MOTION_NOTIFY){



        if(event->x<gtk_adjustment_get_value(adj_horizontal)+FONT){
            return FALSE;
        }
        x=(int)event->x/FONT;


        if(x>10){
            return FALSE;
        }
        prep=(event->y/gtk_adjustment_get_page_size(adj_vertical))/*gtk_widget_get_allocated_height(scrolled_window4)*/;
    //    printf("prep %f\n",prep);
        y=(int)prep;
        if(y>=list_size_interrupts)
            y=list_size_interrupts;
        for(int i=0;i<y;i++){
            delay+=temp->delay_time;
            temp=temp->next;

        }
        temp_elements=temp->pointer;
        for(int i=1;i<x;i++){
            temp_elements=temp_elements->next;

        }

       // printf("x %d  y %d \n",x,y);

        g_sprintf (tesxas,"CPU0 %"PRIu64" \nCPU1 %"PRIu64"  \nCPU2 %"PRIu64"  \nCPU3 %"PRIu64" \n %s \n %d "
                ,
                temp_elements->interrupts.CPU0,
                temp_elements->interrupts.CPU1,
                temp_elements->interrupts.CPU2,
                temp_elements->interrupts.CPU3,
                temp_elements->interrupts.irq,
                   delay
        );



        gtk_widget_set_tooltip_markup (widget,
                                       tesxas);



    }




    return FALSE;
}

gboolean motion_notify_event_net(GtkWidget *widget, GdkEventMotion *event, Network *array)
{
    double x;
    double delay=0;
    int a=0;
    Network *temp=array;

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
                gtk_widget_set_tooltip_markup (widget,
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

            gtk_widget_set_tooltip_markup (widget,
                                           tesxas);



        }

    }





    return TRUE;
}


gboolean
motion_notify_event_memory(GtkWidget *widget, GdkEventMotion *event, Memory_list *array)
{
    double x;
    double delay=0;
    int a=0;
    Memory_list *temp=array;

    gchar tesxas[100];


    if(event->type==GDK_BUTTON_PRESS_MASK){
        return FALSE;
    }


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
                gtk_widget_set_tooltip_markup (widget,
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

            gtk_widget_set_tooltip_markup (widget,
                                           tesxas);



        }

    }





    return TRUE;
}

gboolean motion_notify_event_cpu(GtkWidget *widget, GdkEventMotion *event, Cpu_list *array)
{
    double x=0;
    int delay=0;
    int a=0;


    gchar tesxas[100];

    if(event->type==GDK_BUTTON_PRESS_MASK){
        printf("we left by button press\n");
        return FALSE;
    }


    if(event->type==GDK_MOTION_NOTIFY){

        x=event->x;

        if(x<FONT-2){
            return FALSE;
        }
        if(fmod(x,FONT)<=2 && fmod(x,FONT)>=0 ){

            if(x<=FONT+2){

                g_sprintf (tesxas,"Cpu0 %.2f \nCpu1 %.2f \n"
                        "Cpu2 %.2f \nCpu3 %.2f",0.0,0.0,0.0,0.0);
                gtk_widget_set_tooltip_markup (widget,
                                               tesxas);

                return TRUE;
            }

            a=(int)((x/FONT)-1)*INCREMENT;


            while(array->next!=NULL){
                delay+=array->delay_time;
                if(delay==a){
                    break;
                }
                if(delay>a){

                    return FALSE;
                }
                array=array->next;
            }

            g_sprintf (tesxas,"Cpu0 %.2f \nCpu1 %.2f \n"
                    "Cpu2 %.2f \nCpu3 %.2f\n delay %d",array->data[0],array->data[1],array->data[2],array->data[3],a);

            gtk_widget_set_tooltip_markup (widget,
                                           tesxas);

            return TRUE;

        }




    }





    return FALSE;
}