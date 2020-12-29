//
// Created by dushn on 10.11.20..
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <memory.h>
#include <stdbool.h>
#include <math.h>
#include <inttypes.h>
#include "drawing.h"



/**
 * function do_drawing_cpu(): draws the entire graph, the lines, the frame the seconds and the percentage
 * input:pointer to the graph, pointer to the canvas, step between data, and pointer to the array of cpu usage
 * output:none.
 * */
void do_drawing_cpu2(GtkWidget *widget, cairo_t *cr, guint position, Cpu_list *array1, double height, int counter) {


    double font_size = 10;












    cairo_set_line_width(cr, 1);


    cairo_set_font_size(cr, font_size);

    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);





    for(__int32_t i=0;i<CPU_NUM;i++){/*draws the lines*/
        draw_graph(cr, i, height, font_size, position, array1, counter);
      //  if((*temp_bool)==true){/*display the cpus we want to be displayed*/

       // }
      //  temp_bool++;


    }




}
int position_draw_cpu(Cpu_list **array1, int old_position, int *new_position, int *counter, int step) {
   int  x=((old_position)/step)*INCREMENT;

   // printf("which line %d\n",x);
    *counter=0;
    int delay=0;


    while((*array1)){
        delay+=(*array1)->delay_time;

        if(delay== x){
            if((*array1)->next==NULL){
                printf("hello there\n");
                (*counter)++;
                break;
            }
            (*array1)= (*array1)->next;
            (*counter)++;
            break;
        }
        if(delay> x){
            delay-=(*array1)->delay_time;
            break;



        }
        (*counter)++;

        (*array1)= (*array1)->next;
      //  printf("%p\n",(*array1));

    }

    *new_position=(delay*step)/INCREMENT;
  //  printf("new_position %d counter %d\n",*new_position,*counter);
    return 0;
}
int position_draw_net(Network **array1, int old_position, int *new_position, int *counter, __uint64_t *max_number) {
    int  x=((old_position/FONT))*INCREMENT;

 //   printf("which line %d\n",x);

    int delay=0;
    Network *temp=NULL;

    while((*array1)){
        delay+=(*array1)->delay_time;

        if(delay== x){

            (*array1)= (*array1)->next;
            (*counter)++;
            break;
        }
        if(delay> x){
            delay-=(*array1)->delay_time;
            break;



        }
        (*counter)++;

        (*array1)= (*array1)->next;


    }
    temp=(*array1);

    while(temp){

        if(temp->received_bytes>temp->transmited_bytes){
            if(temp->received_bytes>*max_number){
                *max_number=temp->received_bytes;
            }
        }else{
            if(temp->transmited_bytes>*max_number){
                *max_number=temp->transmited_bytes;
            }
        }
        temp=temp->next;
    }

     *new_position=(delay*FONT)/INCREMENT;
    return 0;
}
gboolean on_draw_event_cpu_mem(GtkWidget *widget, cairo_t *cr, void *array1) {
    double height;


    double value_h;
    double value_v;
    int font_size=10;

    GtkAdjustment *adj_p;

    int counter=0;
    int position=0;
    __uint64_t max_number=0;

    Interrupts_List *p=NULL;

    Interrupts_elements *temp_intrp=NULL;

    if(widget==graph){
        height = gtk_widget_get_allocated_height(cpu_swindow);
       // printf("value  %f \n",gtk_adjustment_get_value(adj));
        adj   =  gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(viewport));
       // printf("upper after %f \n",gtk_adjustment_get_upper(adj));
        adj_p=adj;
        value_h=gtk_adjustment_get_value(adj);

        Cpu_list *temp=array1;
        gtk_widget_set_size_request(widget,(gint)((count/250)*FONT+2*FONT) ,0);
        position_draw_cpu(&temp, (int) value_h, &position, &counter, FONT);
        if(temp==NULL){
            printf("%d \n",counter);
        }
        do_drawing_cpu2(widget, cr,(guint) position, temp, height - 2*font_size, counter);
        draw_time(cr, height-font_size, font_size, (guint)value_h);
        draw_percentages(cr, height - 2 * font_size, font_size, value_h, adj_p, FONT);
        draw_lines(cr, height - 2 * font_size, (int) value_h, count / INCREMENT, FONT,
                   (int) value_h/ FONT, 0, false);
    }
    else if(widget==graph2 ){
        height = gtk_widget_get_allocated_height(scrolled_window2);
        adj_p=adj2;
        value_h=gtk_adjustment_get_value(adj_p);


        gtk_widget_set_size_request(widget,(gint)((count/250)*(FONT)+2*FONT) ,0);

        cairo_set_line_width(cr, 1);


        cairo_set_font_size(cr, font_size);

        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
        draw_time(cr, height-font_size, font_size, (guint)value_h);

        height-=2*font_size;
        draw_graph_mem(cr, 0, font_size, array1, height);
        draw_graph_mem(cr, 1, font_size, array1, height);
        draw_percentages(cr, height, font_size, value_h, adj_p, FONT);
        draw_lines(cr, height, (int) value_h, count / INCREMENT, FONT,
                   (int) value_h / FONT, 0, NULL);



    }
    else if(widget==graph3){
        height = gtk_widget_get_allocated_height(scrolled_window3);
        gtk_widget_set_size_request(widget,(gint)((count/250)*(FONT)+2*FONT) ,0);

        adj_p=adj3;
        cairo_set_line_width(cr, 1);


        cairo_set_font_size(cr, font_size);

        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);

        value_h=gtk_adjustment_get_value(adj_p);
        Network *temp_net=array1;


        draw_time(cr, height-1*font_size, font_size, (guint)value_h);

        height-=2*font_size;
        position_draw_net(&temp_net,(int)value_h, &position, &counter,&max_number);

        draw_graph_net(cr, 0, height,font_size,temp_net,max_number,counter,position);
        draw_graph_net(cr, 1, height,font_size,temp_net,max_number,counter,position);
        draw_lines(cr, height, (int) value_h, count / INCREMENT, FONT,
                   (int) value_h / FONT, 0, false);
        draw_network_sidebar(cr, height, font_size, value_h, adj_p, max_number, true, 0, FONT);



    }else{
        p=interrupts_list;
        adj_p=adj_horizontal;
        height = gtk_widget_get_allocated_height(scrolled_window4);


        value_h=gtk_adjustment_get_value(adj_p);
        value_v=gtk_adjustment_get_value(adj_vertical);



        gtk_widget_set_size_request(widget,(gint)(10*FONT+2*FONT) ,(gint)(height*list_size_interrupts));


        cairo_set_line_width(cr, 1);

        cairo_set_font_size(cr, font_size);

        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);


        height-=2*font_size;

        draw_lines(cr, height, (int) value_h, 10/*(int) gtk_adjustment_get_upper(adj_p) / FONT*/,
                   FONT, (int) value_h / FONT, (int) value_v,
                   true);

        int t=(int)value_v/(int) gtk_adjustment_get_page_size(adj_vertical);

        if(t>=list_size_interrupts){
            t=list_size_interrupts-1;
        }

            for(int i=0;i<t;i++){
                p=p->next;


            }


        draw_network_sidebar(cr, height, font_size, value_h, adj_horizontal, p->max_number, false, value_v, FONT);
        temp_intrp=p->pointer;
        for(int i=0;i<(int)value_h/FONT;i++){

            temp_intrp=temp_intrp->next;

        }


        draw_interrupts(cr, value5 + height + font_size, font_size, (int) value_h, temp_intrp, height,
                        (int) p->max_number, FONT);

    }





    return true;
}

void draw_network_sidebar(cairo_t *cr, double height, double font_size, double position, GtkAdjustment *adj_p,
                          __uint64_t max_number, bool net_int, double position_y, double step) {



    char buffer[10]={0};
    double upper=gtk_adjustment_get_upper(adj_p);
    int number=(int)position%(int)step;
        number=(int)step-number;

    cairo_set_font_size(cr, font_size);

    cairo_set_source_rgb(cr, 0, 1, 1);
    if(net_int==true){
     //   printf("number %d  %d\n",number,(int)position%(int)step);
        cairo_rectangle(cr,position,height,step-2,-height);

    }  else{
        cairo_rectangle(cr,position,position_y,step-2,height);

    }




    cairo_fill(cr);
    cairo_set_source_rgb(cr, 0, 0, 0);

    if(net_int==true){
        cairo_move_to(cr, position,font_size);
        cairo_show_text(cr, g_format_size_full(max_number,G_FORMAT_SIZE_IEC_UNITS));
    }  else{
        cairo_move_to(cr, position,position_y+font_size);
        sprintf(buffer,"%" SCNu64 "",max_number);
        cairo_show_text(cr,buffer ) ;
    }

    cairo_set_source_rgba(cr, 0, 0, 0,0.4);

    if(net_int==true){
        cairo_move_to(cr, position, 0);
        cairo_line_to(cr,upper-number,0);
    }  else{
        cairo_move_to(cr, position+step, position_y);
        cairo_line_to(cr,upper-number,position_y);
    }



    cairo_set_source_rgb(cr, 0, 0, 0);

    if(net_int==true){
        cairo_move_to(cr,  position, height / 4);
        cairo_show_text(cr,  g_format_size_full(max_number*3/4,G_FORMAT_SIZE_IEC_UNITS));
    }  else{
        cairo_move_to(cr,  position,position_y+ height/4);
        sprintf(buffer,"%" SCNu64 "",max_number*3/4);
        cairo_show_text(cr,buffer ) ;

    }

    cairo_set_source_rgba(cr, 0, 0, 0,0.4);

    if(net_int==true){
        cairo_move_to(cr,  position+step, height / 4);
        cairo_line_to(cr,upper-number,height / 4);
    }  else{
        cairo_move_to(cr,  position+step,position_y+ height/4);
        cairo_line_to(cr,upper-number,position_y+ height/4);
    }


    cairo_set_source_rgb(cr, 0, 0, 0);

    if(net_int==true){
        cairo_move_to(cr,  position, height / 2);
        cairo_show_text(cr,  g_format_size_full(max_number/2,G_FORMAT_SIZE_IEC_UNITS));
    }  else{
        cairo_move_to(cr,  position,position_y+ height/2);
        sprintf(buffer,"%" SCNu64 "",max_number/2);
        cairo_show_text(cr,buffer ) ;
    }

    cairo_set_source_rgba(cr, 0, 0, 0,0.4);

    if(net_int==true){
        cairo_move_to(cr,  position+step, (height /  2));
        cairo_line_to(cr,upper-number,height / 2);
    }  else{
        cairo_move_to(cr,  position+step,position_y+ height/2);
        cairo_line_to(cr,upper-number,position_y+height / 2);
    }


    cairo_set_source_rgb(cr, 0, 0, 0);

    if(net_int==true){
        cairo_move_to(cr,  position, height / 4 * 3);
        cairo_show_text(cr,  g_format_size_full(max_number/4,G_FORMAT_SIZE_IEC_UNITS));
    }  else{
        cairo_move_to(cr,  position,position_y+ height/4 * 3);
        sprintf(buffer,"%" SCNu64 "",max_number/4);
        cairo_show_text(cr,buffer ) ;
    }

    cairo_set_source_rgba(cr, 0, 0, 0,0.4);


    if(net_int==true){
        cairo_move_to(cr,  position+step, height / 4 * 3);
        cairo_line_to(cr,upper-number,height / 4*3);
    }  else{
        cairo_move_to(cr,  position+step,position_y+ height/4 * 3);
        cairo_line_to(cr,upper-number,position_y+ height/4 * 3);
    }


    cairo_set_source_rgb(cr, 0, 0, 0);

    if(net_int==true){
        cairo_move_to(cr,  position, height);
        cairo_show_text(cr,  g_format_size_full(0,G_FORMAT_SIZE_IEC_UNITS));
    }  else{
        cairo_move_to(cr,  position,position_y+ height);
        cairo_show_text(cr, "0") ;
    }

    cairo_set_source_rgba(cr, 0, 0, 0,0.4);

    if(net_int==true){
        cairo_move_to(cr,  position+step, height);
        cairo_line_to(cr,upper-number,height );
    }  else{
        cairo_move_to(cr,  position+step, position_y+height);
        cairo_line_to(cr,upper-number,position_y+height );
    }


    cairo_stroke(cr);


}


void draw_percentages(cairo_t *cr, double height, double font_size, double position, GtkAdjustment *adj_p, int step) {




    double upper=gtk_adjustment_get_upper(adj_p);

    int number=(int)position%step;
    number=step-number;
    cairo_set_font_size(cr, font_size);

    cairo_set_source_rgb(cr, 0, 1, 1);

        cairo_rectangle(cr,position,height,step-2,-height);


    cairo_fill(cr);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr, position,font_size);
    cairo_show_text(cr, "100%");
    cairo_set_source_rgba(cr, 0, 0, 0,0.4);
    cairo_move_to(cr, position+step, 0);
    cairo_line_to(cr,upper-number,0);
   //


    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr,  position, height / 4);
    cairo_show_text(cr, "75%");
    cairo_set_source_rgba(cr, 0, 0, 0,0.4);
    cairo_move_to(cr,  position+step, height / 4);
    cairo_line_to(cr,upper-number,height / 4);


    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr,  position, height /  2);
    cairo_show_text(cr, "50%");
    cairo_set_source_rgba(cr, 0, 0, 0,0.4);
    cairo_move_to(cr,  position+step, (height /  2));
    cairo_line_to(cr,upper-number,height / 2);


    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr,  position, height / 4 * 3);
    cairo_show_text(cr, "25%");
    cairo_set_source_rgba(cr, 0, 0, 0,0.4);
    cairo_move_to(cr,  position+step, height / 4 * 3);
    cairo_line_to(cr,upper-number,height / 4*3);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr,  position, height);
    cairo_show_text(cr, "0%");
    cairo_set_source_rgba(cr, 0, 0, 0,0.4);
    cairo_move_to(cr,  position+step, height);
    cairo_line_to(cr,upper-number,height );

    cairo_stroke(cr);


}


void draw_lines(cairo_t *cr, double height, int x, int number_lines, double step, int number_start, int y, bool inter) {





    int step_count=0;


    cairo_set_source_rgba(cr, 0, 0, 0,0.4);







    for (int j = number_start; j <=number_lines; j++) {



    if(inter==false){
        cairo_move_to(cr,x + step, height);//set right after the percentage

        cairo_line_to(cr,x +step,-height );//straight line to the top
        cairo_translate(cr,step,0);
    }else{
        cairo_move_to(cr,x + step, y);//set right after the percentage

        cairo_line_to(cr,x +step,y+height );//straight line to the top
        cairo_translate(cr,step,0);
    }





        step_count+=step;




    }

    cairo_stroke(cr);

        cairo_translate(cr, -step_count, 0);

}
void draw_time(cairo_t *cr, double height, double font_size, int x) {



    double step = 0;
    int count_temp=0;
    int step_count=0;
    int number=0;



        cairo_set_source_rgb(cr, 1, 0, 0);//rgb


    char buffer[64];


        step=6 * font_size;



    number=x/FONT;
    count_temp +=  INCREMENT*number;
    cairo_move_to(cr,x+ step, height);
    sprintf(buffer,"%d",count_temp);
    cairo_show_text(cr, buffer);

    cairo_translate(cr,step,0);
    step_count+=step;
    for (int j = number; j < count/INCREMENT; j++) {
        memset(buffer,0,sizeof(buffer));
        count_temp +=  INCREMENT;
        double num_font=  sprintf(buffer,"%d",count_temp);
       // printf("num %d\n",num_font);
        cairo_move_to(cr,x+ step-num_font*num_font/2, height);


      //  sprintf(buffer,"%d",count_temp);
        cairo_show_text(cr, buffer);
        cairo_translate(cr,step,0);
        step_count+=step;



    }

    cairo_stroke(cr);
    cairo_translate(cr,-step_count,0);

}
/*
 * function draw_graph(): draws the lines on the graph
 * input: pointer to the canvas,index of the data,width,height,font size, step between
 * data, pointer to the cpu_array of data
 * output:none.
 * */
void
draw_graph(cairo_t *cr, int r, double height, double font_size, int position, Cpu_list *array, int counter) {

    Cpu_list *temp = array;
    double prev  ;
    double step = 0;
    double step_counter=0;

    double delay=0;


    gfloat peak;
    double percentage=0;

    if (r == 0) {

        cairo_set_source_rgb(cr, 1, 0, 0);//rgb
    } else if (r == 1 ) {

        cairo_set_source_rgb(cr, 0, 1, 0);
    } else if (r == 2 ) {

        cairo_set_source_rgb(cr, 0, 0, 1);
    }  else if (r == 3 ) {

        cairo_set_source_rgb(cr, 1, 0.5, 0);
    }


    if(counter==0  ){
        prev = height;
   }else{
        percentage = ((height ) / 100) * temp->prev->data[r];
        prev = height - percentage;
    }
    //printf("prev %f percentage %f data %f \n",prev,percentage,temp->data[r]);
    for (int j = counter; j < list_num_size; j++) {



        peak = temp->data[r];
        delay=temp->delay_time;


        cairo_move_to(cr,position+ 6 * font_size, prev);



        percentage = ((height ) / 100) * peak;

       step=6 * font_size*(delay/INCREMENT);

        step_counter+=step;


        if (percentage == height) {
            percentage = height - 1;
        }

        prev = height - percentage;
        cairo_line_to(cr,position+ step +FONT, prev );

        cairo_translate(cr, step, 0);

        temp = temp->next;


    }




    cairo_stroke(cr);


    cairo_translate(cr, -step_counter , 0);  /*return to the start of the graph*/




}
void
draw_graph_net(cairo_t *cr, int r, double height, double font_size,
               Network *array, __uint64_t max_number, int counter, int position) {

    Network *temp=array;
    double prev;
    double step         = 0;
    gfloat peak;
    double percentage;
    double step_counter = 0;
    double delay        = 0;







    if (r == 0) {
        cairo_set_source_rgb(cr, 1, 0, 0);//rgb
    } else {
        cairo_set_source_rgb(cr, 0, 1, 0);
    }

    if(counter==0  ){
        prev = height;
    }else{
        if(max_number==0){
            percentage=0;
        }else{
            if(r==0){
                percentage = ((height ) / max_number) * temp->prev->transmited_bytes;
            }else{
                percentage = ((height ) / max_number) * temp->prev->received_bytes;
            }
        }


        prev = height - percentage;
    }

    for (__int32_t j = counter; j < list_num_size_net; j++) {


        if(r==0){
            peak = temp->transmited_bytes;
        }else{
            peak = temp->received_bytes;
        }
        delay=temp->delay_time;



        cairo_move_to(cr, position+6 * font_size, prev);


        /*if its network usage we move the graph by 5 so we can have space for the data/s stat on the right*/


        if(max_number==0){
            percentage=0;
        }else{//diving by zero gets us infinity
            percentage      = ((height) / max_number) * peak;
        }


        step            =6 * font_size*(delay/INCREMENT);

        step_counter   +=step;


        if (percentage == height) {
            percentage = height - 1;
        }

        prev = height - percentage;
        if (prev == height) {
            prev = height - 1;
        }
        cairo_line_to(cr,position+ step +FONT, prev );



        cairo_translate(cr, step, 0);

        temp = temp->next;

    }



    cairo_stroke(cr);


    cairo_translate(cr, -step_counter, 0);  /*return to the start of the graph*/



}
void
draw_graph_mem(cairo_t *cr, int r, int font_size, Memory_list *array, double height) {

    Memory_list *temp=array;
    double prev=height;
    double step = 0;
    double delay=0;
    double step_counter=0;
    gfloat peak;
    double percentage;






    if (r == 0) {
        cairo_set_source_rgb(cr, 1, 0, 0);//rgb
    } else {
        cairo_set_source_rgb(cr, 0, 1, 0);
    }

    for (__int32_t j = 0; j < list_num_size_memory; j++) {



        if (r == 0) {
           peak=temp->memory_used*100/temp->memory_total;

            }
        else{
            peak=temp->swap_used*100/temp->swap_total;
        }

        delay=temp->delay_time;



        cairo_move_to(cr, FONT, prev);



            percentage = ((height ) / 100) * peak;
            step =FONT*(delay/INCREMENT);
        step_counter+=step;



        if (percentage == height) {
            percentage = height - 1;
        }

        prev = height - percentage;
        cairo_line_to(cr, step +6*font_size, prev );

        cairo_translate(cr, step, 0);
        temp = temp->next;

    }




    cairo_stroke(cr);


    cairo_translate(cr, -step_counter, 0);  /*return to the start of the graph*/



}
void
draw_interrupts(cairo_t *cr, double y, double font_size, int x, Interrupts_elements *array, double height,
                int max_number, double step) {



    double step_count = 0;





   while(array){


       cairo_set_source_rgb(cr, 1, 0, 0);
       cairo_rectangle(cr,x + step,y-font_size,step/4,-((height) / max_number) * array->interrupts.CPU0);
       cairo_fill(cr);
       cairo_set_source_rgb(cr, 0, 1, 0);
       cairo_rectangle(cr,x + step+step/4,y-font_size,step/4,-((height) / max_number) * array->interrupts.CPU1);
       cairo_fill(cr);
       cairo_set_source_rgb(cr, 0, 0, 1);
       cairo_rectangle(cr,x + step+step/2,y-font_size,step/4,-((height) / max_number) * array->interrupts.CPU2);
       cairo_fill(cr);
       cairo_set_source_rgb(cr, 1, 0.5, 0);
       cairo_rectangle(cr,x + step+step/4*3,y-font_size,step/4,-((height) / max_number) * array->interrupts.CPU3);
       cairo_fill(cr);

    cairo_move_to(cr, x + step, y);



       cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_show_text(cr, array->interrupts.irq);
    cairo_translate(cr, step, 0);
    step_count += step;


    array = array->next;
}

    cairo_stroke(cr);
    cairo_translate(cr,-step_count,0);




}
