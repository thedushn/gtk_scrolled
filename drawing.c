//
// Created by dushn on 10.11.20..
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <memory.h>
#include <stdbool.h>
#include "drawing.h"
#include "reading.h"


/**
 * function do_drawing_cpu(): draws the entire graph, the lines, the frame the seconds and the percentage
 * input:pointer to the graph, pointer to the canvas, step between data, and pointer to the array of cpu usage
 * output:none.
 * */
void do_drawing_cpu2(GtkWidget *widget, cairo_t *cr, guint time_step, Cpu_list *array1) {

    gint width, height;
    double font_size = 10;
   // bool *temp_bool=cpu_status;
    double size_scale=  gtk_adjustment_get_upper(adj);
  //  printf("size %.0f\n",size_scale);
  //  gtk_widget_get_size_request(widget,&width,&height);
    width=gtk_widget_get_allocated_width(scrolled_window);
    height=gtk_widget_get_allocated_height(scrolled_window);
    gtk_widget_set_size_request(widget,(gint)((count/250)*(6*font_size)+18*font_size) ,0);
   upper=  gtk_adjustment_get_upper(adj)-gtk_adjustment_get_page_size(adj);
  //  printf("size %.0f\n",size_scale);
  //  size_scale=  gtk_adjustment_get_upper(adj);
  //  printf("size %.0f\n",size_scale);
   //   gtk_adjustment_set_upper(adj,((count/250)*(6*font_size)+8*font_size));
//    size_scale=  gtk_adjustment_get_upper(adj);
   // printf("size %.0f\n",size_scale);
   // width=gtk_widget_get_allocated_width(window);
    //height=80;
    height-=2*font_size;

    //gtk_adjustment_set_step_increment(adj,250);
    //gtk_adjustment_set_value(adj,(6*font_size)+3*font_size);
//    double temp=gtk_adjustment_get_value(adj);
//    if(value<temp){
//        value-=60;
//        if(value<0){
//            gtk_adjustment_set_value(adj,0);
//            value=0;
//        }else{
//            gtk_adjustment_set_value(adj,value);
//        }
//
//
//    }else{
//        value+=60;
//        gtk_adjustment_set_value(adj,value);
//
//    }
   // gtk_adjustment_set_value(adj,(9*font_size));
//  double size_scale=  gtk_adjustment_get_lower(adj);
// size_scale=  gtk_adjustment_get_upper(adj);

   // printf("%f \n",gtk_adjustment_get_upper(adj));




    cairo_set_line_width(cr, 1);


    cairo_set_font_size(cr, font_size);

    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);


   // draw_frame(cr, width, height, font_size, 3);
  //  draw_percentages(cr, height, font_size, 0);



    for(__int32_t i=0;i<CPU_NUM;i++){/*draws the lines*/
        draw_graph(cr, i, width, height, font_size, time_step, array1);
      //  if((*temp_bool)==true){/*display the cpus we want to be displayed*/

       // }
      //  temp_bool++;


    }

    draw_time(cr, 5,width, height, font_size, 3,array1);
   // draw_lines(cr, height, font_size,array1);

  // writing_seconds(cr, width, height, font_size, 3);

}
gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, Cpu_list *array1) {
    double height,width;
    double value;
    GtkAdjustment *adj_p;
    if(widget==graph){
        height = gtk_widget_get_allocated_height(scrolled_window);
        width = gtk_widget_get_allocated_width(scrolled_window);
        printf("windwo  %f %f \n",height,width);
        value=value1;
        adj_p=adj;
    }
    else if(widget==graph2){
        height = gtk_widget_get_allocated_height(scrolled_window2);
        width = gtk_widget_get_allocated_width(scrolled_window2);
        value=value2;
        printf("windwo 2 %f %f \n",height,width);
        adj_p=adj2;
    }
    else{
        height = gtk_widget_get_allocated_height(scrolled_window3);
        width = gtk_widget_get_allocated_width(scrolled_window3);
        value=value3;
        printf("windwo 3 %f %f \n",height,width);
        adj_p=adj3;
    }






    do_drawing_cpu2(widget, cr,1000,array1);
    draw_percentages(cr, height, 10, value, adj_p);
    draw_lines(cr,height-20,10,array1);

    return true;
}
gboolean on_draw_event2(GtkWidget *widget, cairo_t *cr) {

  double  height=gtk_widget_get_allocated_height(window);
  //  draw_percentages(cr, height, 10, value);
    return true;
}
void writing_seconds(cairo_t *cr, double width, double height, double font_size, int i) {


    const char *name = "0 sec";
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr, (double) i * font_size, height);
    cairo_show_text(cr, name);
    cairo_move_to(cr, (width - i * 2 * font_size) / 6 + i * font_size, height);
    cairo_show_text(cr, "10 sec");
    cairo_move_to(cr, (width - i * 2 * font_size) / 6 * 2 + i * font_size, height);
    cairo_show_text(cr, "20 sec");
    cairo_move_to(cr, (width - i * 2 * font_size) / 6 * 3 + i * font_size, height);
    cairo_show_text(cr, "30 sec");
    cairo_move_to(cr, (width - i * 2 * font_size) / 6 * 4 + i * font_size, height);
    cairo_show_text(cr, "40 sec");
    cairo_move_to(cr, (width - i * 2 * font_size) / 6 * 5 + i * font_size, height);
    cairo_show_text(cr, "50 sec");
    cairo_move_to(cr, width - i * font_size, height);
    cairo_show_text(cr, "60 s");
    cairo_stroke_preserve(cr);

    cairo_set_source_rgba(cr, .7, .7, .7, 0.5);
    for (int g = 1; g <= 5; g++) {
        cairo_move_to(cr, (width - 2 * i * font_size) / 6 * g + i * font_size, height - font_size);
        cairo_line_to(cr, (width - 2 * i * font_size) / 6 * g + i * font_size, 0);
    }
    cairo_stroke(cr);


}
void draw_percentages(cairo_t *cr, double height, double font_size, double position, GtkAdjustment *adj_p) {

    double prev = height - 2*font_size; //zero

    double temp2=gtk_adjustment_get_upper(adj_p);
    printf("Position %f  %f\n",position,temp2);
    cairo_set_font_size(cr, font_size);

    cairo_set_source_rgb(cr, 0, 1, 1);
//    if(position==upper){
//        printf("hello there dumb fuck \n");
//        cairo_rectangle(cr,position,height-2*font_size,6*font_size,-height);
//    }else{
        cairo_rectangle(cr,position,height-3*font_size,3*font_size-2,-height);
 //   }

    cairo_fill(cr);
    cairo_move_to(cr, position, font_size);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_show_text(cr, "100%");
    cairo_move_to(cr, position, prev / 4);
    cairo_show_text(cr, "75%");
    cairo_move_to(cr, position, prev / 4 * 2);
    cairo_show_text(cr, "50%");
    cairo_move_to(cr, position, prev / 4 * 3);
    cairo_show_text(cr, "25%");
    cairo_move_to(cr, position, prev-2*font_size);
    cairo_show_text(cr, "0%");
    cairo_stroke(cr);


}


void draw_lines(cairo_t *cr, double height, double font_size, Cpu_list *array){

    Cpu_list *temp = array;
    double prev = height - 2*font_size; //zero
    double step = 0;
    int count_temp=0;
    int step_count=0;


        cairo_set_source_rgb(cr, 1, 0, 0);//rgb







    for (int j = 0; j <=count/INCREMENT; j++) {




       // count_temp +=  temp->delay_time;
        cairo_move_to(cr, 3 * font_size, prev);//set right after the percentage

        cairo_line_to(cr, 3 * font_size,-height );//straight line to the top

       // step=6 * font_size*(temp->delay_time/250);
        step=6 * font_size;
        step_count+=step;
        cairo_translate(cr,step,0);
        //    cairo_move_to(cr, (double) j * step, prev);



     //   temp=temp->next;


    }
 //   printf("Last %d\n",count_temp);
    cairo_stroke(cr);
    cairo_translate(cr,-step_count,0);

}
void draw_time(cairo_t *cr, int r, double width, double height, double font_size, double time_step, Cpu_list *array){

    Cpu_list *temp = array;
    double prev = height - font_size; //zero
    double step = 0;
    int count_temp=0;
    int step_count=0;


    if (r == 0)
        cairo_set_source_rgb(cr, 1, 0, 0);//rgb


    char buffer[64];

    cairo_move_to(cr, 3 * font_size, prev);
    cairo_show_text(cr, "0");
    step=6 * font_size;
    cairo_translate(cr,step,0);
    step_count+=step;
//    step=6 * font_size*(temp->delay_time/250);
//    cairo_translate(cr,step,0);
//    step_count+=step;
//    count_temp +=  temp->delay_time;
//    temp=temp->next;
    step=6 * font_size;
    for (int j = 0; j </*list_num_size-1*/ count/INCREMENT; j++) {
        memset(buffer,0,sizeof(buffer));

        cairo_move_to(cr, 3 * font_size, prev);
        count_temp +=  INCREMENT;

        sprintf(buffer,"%d",count_temp);
        cairo_show_text(cr, buffer);
        cairo_translate(cr,step,0);
        step_count+=step;
//        count_temp +=  temp->delay_time;
//        sprintf(buffer,"%d",count_temp);
//        cairo_move_to(cr, 3 * font_size, prev);
//        cairo_show_text(cr, buffer);
//        step=6 * font_size*(temp->delay_time/250);
//        step_count+=step;
//        cairo_translate(cr,step,0);




      //  temp=temp->next;


    }
//    for (int j = 0; j <list_num_size; j++) {
//            memset(buffer,0,sizeof(buffer));
//      //  cairo_move_to(cr, 6 * font_size, prev);
//
//
//        count_temp +=  temp->delay_time;
//        sprintf(buffer,"%d",count_temp);
//        cairo_move_to(cr, 3 * font_size, prev);
//        cairo_show_text(cr, buffer);
//        step=6 * font_size*(temp->delay_time/250);
//        step_count+=step;
//        cairo_translate(cr,step,0);
//        //    cairo_move_to(cr, (double) j * step, prev);
//
//
//
//        temp=temp->next;
//
//
//    }
  //  printf("Last %d\n",count_temp);
    cairo_stroke(cr);
    cairo_translate(cr,-step_count,0);

}
/*
 * function draw_graph(): draws the lines on the graph
 * input: pointer to the canvas,index of the data,width,height,font size, step between
 * data, pointer to the array of data
 * output:none.
 * */
void
draw_graph(cairo_t *cr, int r, double width, double height, double font_size, double time_step, Cpu_list *array) {

    Cpu_list *temp = array;
    double prev = height - 2*font_size; //zero
    double step = 0;
    double step_counter=0;
    double delay=0;
    gfloat peak;
    double percentage;
    if (r == 0) {

        cairo_set_source_rgb(cr, 1, 0, 0);//rgb
    } else if (r == 1 ) {

        cairo_set_source_rgb(cr, 0, 1, 0);
    } else if (r == 2 ) {

        cairo_set_source_rgb(cr, 0, 0, 1);
    }  else if (r == 3 ) {

        cairo_set_source_rgb(cr, 1, 0.5, 0);
    }


//
//    peak = temp->data[r];
//    delay = temp->delay_time;
//    cairo_move_to(cr, 3 * font_size, prev);
//    percentage = ((height - font_size) / 100) * peak;
//
//
//
//    if (percentage == height) {
//        percentage = height - 1;
//    }
//
//    prev = height - font_size - percentage;
//    cairo_line_to(cr,3*font_size, prev );
//
//   // cairo_translate(cr, step, 0);
//
//    temp = temp->next;


    for (int j = 0; j < list_num_size; j++) {



        peak = temp->data[r];
        delay=temp->delay_time;


        cairo_move_to(cr, 3 * font_size, prev);



        percentage = ((height - font_size) / 100) * peak;
       // step = (width - 3 * font_size - 3 * font_size) / (temp->delay_time);
       step=6 * font_size*(delay/INCREMENT);

        step_counter+=step;


        if (percentage == height) {
            percentage = height - 1;
        }

        prev = height - font_size - percentage;
        cairo_line_to(cr, step +3*font_size, prev );

        cairo_translate(cr, step, 0);

        temp = temp->next;


    }


  //  cairo_line_to(cr, 3 * font_size, height - font_size);/* the last line always touches the floor*/

    cairo_stroke(cr);


    cairo_translate(cr, -step_counter , 0);  /*return to the start of the graph*/


}
void draw_frame(cairo_t *cr, double width, double height, double font_size, int i) {



    //frame
    cairo_set_source_rgb(cr, 0, 0, 0);

    cairo_rectangle(cr, i * font_size, height - font_size, width - 2 * i * font_size, -height + font_size);
    cairo_stroke_preserve(cr);

    cairo_set_source_rgba(cr, 1.0, 0.43, 0.0, 0.3);
    cairo_fill(cr);
    //Percentage line
    cairo_set_source_rgba(cr, .7, .7, .7, 0.5);
    cairo_move_to(cr, i * font_size, (height - font_size) / 4);//75%
    cairo_line_to(cr, width - i * font_size, (height - font_size) / 4);
    cairo_move_to(cr, i * font_size, (height - font_size) / 4 * 2);//50
    cairo_line_to(cr, width - i * font_size, (height - font_size) / 4 * 2);
    cairo_move_to(cr, i * font_size, (height - font_size) / 4 * 3);//25
    cairo_line_to(cr, width - i * font_size, (height - font_size) / 4 * 3);
    cairo_stroke(cr);


}