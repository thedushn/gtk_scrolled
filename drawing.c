//
// Created by dushn on 10.11.20..
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <memory.h>
#include <stdbool.h>
#include "drawing.h"


/**
 * function do_drawing_cpu(): draws the entire graph, the lines, the frame the seconds and the percentage
 * input:pointer to the graph, pointer to the canvas, step between data, and pointer to the array of cpu usage
 * output:none.
 * */
void do_drawing_cpu2(GtkWidget *widget, cairo_t *cr, guint time_step, Cpu_list *array1) {
    static double value=0;
    gint width, height;
    double font_size = 10;
   // bool *temp_bool=cpu_status;

  //  gtk_widget_get_size_request(widget,&width,&height);
    width=gtk_widget_get_allocated_width(window);
    height=gtk_widget_get_allocated_height(window);
    gtk_widget_set_size_request(widget,(gint)((count/250)*(6*font_size)+3*font_size) ,80);
   // width=gtk_widget_get_allocated_width(window);
    //height=80;
    height-=2*font_size;

    gtk_adjustment_set_page_size(adj,width);
    gtk_adjustment_set_page_increment(adj,(count/250));
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


    cairo_surface_t *graph_surface;
    graph_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, (int) width, (int) height);

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
    draw_lines(cr,height,font_size,array1);

  // writing_seconds(cr, width, height, font_size, 3);

    if (graph_surface != NULL) {
        cairo_set_source_surface(cr, graph_surface, 0.0, 0.0);
        cairo_paint(cr);
        cairo_surface_destroy(graph_surface);


    }

}
gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,Cpu_list *array1) {




    draw_percentages(cr,gtk_widget_get_allocated_height(window),10,value);
    do_drawing_cpu2(widget, cr,1000,array1);

    return true;
}
gboolean on_draw_event2(GtkWidget *widget, cairo_t *cr) {

  double  height=gtk_widget_get_allocated_height(window);
    draw_percentages(cr, height, 10, value);
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
void draw_percentages(cairo_t *cr, double height, double font_size, double position) {

    printf("value %0.f position %0.f\n",value,position);
    cairo_set_font_size(cr, font_size);
    cairo_move_to(cr, position, font_size);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_show_text(cr, "100%");
    cairo_move_to(cr, value, (height - font_size) / 4);
    cairo_show_text(cr, "75%");
    cairo_move_to(cr, value, (height - font_size) / 4 * 2);
    cairo_show_text(cr, "50%");
    cairo_move_to(cr, value, (height - font_size) / 4 * 3);
    cairo_show_text(cr, "25%");
    cairo_move_to(cr, value, height - font_size);
    cairo_show_text(cr, "0%");
    cairo_stroke(cr);


}

int cpu_read(Cpu_list **array) {


    FILE *fp;
    char *filename = "cpu.data";
    char buffer[1024];
    char *p;
    Cpu_list *temp=NULL;
    int ret=0;
    int delay;
    if ((fp = fopen(filename, "r")) == NULL) //create a file if it doesnt exist
        return 1;




    while((fgets(buffer,1024,fp))!=NULL){
        delay=0;
        if(strncmp(buffer,"Time:",5)==0){
            p=strchr(buffer,'D');
            ret= sscanf(p,"Delay %d",&delay);
            if(fgets(buffer,1024,fp)==NULL){
                ret=-1;
                break;
            }

            if (buffer[0]=='\n'){
                if(fgets(buffer,1024,fp)==NULL){
                    ret=-1;
                    break;
                }
            }

        }
        temp = (Cpu_list *) calloc(1, sizeof(Cpu_list));
        if (temp == NULL) {
            printf("calloc error %d \n", errno);
            free(temp);
            ret=-1;
            break;
        }
        temp->next=NULL;
        temp->delay_time=delay;
        if(sscanf(buffer,"%f %f %f %f",&(temp)->data[0],&(temp)->data[1],&(temp)->data[2],&(temp)->data[3])==4){
            if((*array)==NULL){
                (*array) = temp;
            }
            else{
                Cpu_list *temp_p=(*array);
                while(temp_p->next!=NULL){
                    temp_p=temp_p->next;
                }
                temp_p->next=temp;


            }
//            temp->next = (*array);
//            (*array) = temp;
            list_num_size++;
        }
        else{
            printf("sscanf error  \n");
            free(temp);
            ret=-1;
            break;
        }
        count+=delay;




    }




    fclose(fp);
    return ret;

}
void draw_lines(cairo_t *cr, double height, double font_size, Cpu_list *array){

    Cpu_list *temp = array;
    double prev = height - font_size; //zero
    double step = 0;
    int count_temp=0;
    int step_count=0;


        cairo_set_source_rgb(cr, 1, 0, 0);//rgb







    for (int j = 0; j <count/250; j++) {




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


    char buffer[1000];

    cairo_move_to(cr, 3 * font_size, prev);
    cairo_show_text(cr, "0");
    step=6 * font_size;
    cairo_translate(cr,step,0);
//    step_count+=step;
//    step=6 * font_size*(temp->delay_time/250);
//    cairo_translate(cr,step,0);
//    step_count+=step;
//    count_temp +=  temp->delay_time;
//    temp=temp->next;
    for (int j = 0; j </*list_num_size-1*/ count/250; j++) {
        memset(buffer,0,sizeof(buffer));

        cairo_move_to(cr, 3 * font_size, prev);
        count_temp +=  250;
        step=6 * font_size;
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
    double prev = height - font_size; //zero
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
       step=6 * font_size*(delay/250);

        step_counter+=step;


        if (percentage == height) {
            percentage = height - 1;
        }

        prev = height - font_size - percentage;
        cairo_line_to(cr, step +3*font_size, prev );

        cairo_translate(cr, step, 0);

        temp = temp->next;


    }


    cairo_line_to(cr, 3 * font_size, height - font_size);/* the last line always touches the floor*/

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