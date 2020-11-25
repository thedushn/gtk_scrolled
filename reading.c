//
// Created by dushn on 16.11.20..
//


#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "reading.h"


int cpu_read(Cpu_list **array) {


    FILE *fp;
    char *filename = "cpu.data";
    char buffer[1024];
    char *p;
    Cpu_list *temp=NULL;
    Cpu_list *last=NULL;
    int ret=0;
    int delay;
    if ((fp = fopen(filename, "r")) == NULL) //create a file if it doesnt exist
        return -1;




    while((fgets(buffer,sizeof(buffer),fp))!=NULL){
        delay=0;
        if(strncmp(buffer,"Time:",5)==0){
            p=strrchr(buffer,'D');
            ret= sscanf(p,"Delay %d",&delay);
            if(fgets(buffer,1024,fp)==NULL){
                ret=-1;
                break;
            }

            if (buffer[0]=='\n'){
                if(fgets(buffer,sizeof(buffer),fp)==NULL){
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
                last=temp;
            }
            else{
//                Cpu_list *temp_p=(*array);
//                while(temp_p->next!=NULL){
//                    temp_p=temp_p->next;
//                }
//                temp->prev= temp_p;
//                temp_p->next=temp;
                temp->prev= last;
                last->next=temp;
                last=temp;


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

    printf("count %d \n",count);



    fclose(fp);
    return ret;

}
int netw_read(Network **array, __uint64_t *max_number) {

    FILE *fp;
    char *filename = "network.data";
    char *p;

    char buffer[1024]={0};
    int delay=0;
    int ret=0;
    Network *temp=NULL;
    Network *last=NULL;
    *max_number=100;

    if ((fp = fopen(filename, "r")) == NULL) //create a file if it doesnt exist
        return -1;


    while((fgets(buffer,sizeof(buffer),fp))!=NULL){
        delay=0;
        if(strncmp(buffer,"Time:",5)==0){
            p=strrchr(buffer,'D');
            ret= sscanf(p,"Delay %d",&delay);
            if(fgets(buffer,1024,fp)==NULL){
                ret=-1;
                break;
            }

            if (buffer[0]=='\n'){
                if(fgets(buffer,sizeof(buffer),fp)==NULL){
                    ret=-1;
                    break;
                }
            }

        }
        temp = (Network *) calloc(1, sizeof(Network));
        if (temp == NULL) {
            printf("calloc error %d \n", errno);
            free(temp);
            ret=-1;
            break;
        }
        temp->next=NULL;
        temp->delay_time=delay;
        if(sscanf(buffer,"Transmited %" SCNu64 "  Received %" SCNu64 "",&temp->transmited_bytes,&temp->received_bytes)==2){
            if((*array)==NULL){
                (*array) = temp;
                last=temp;
            }
            else{
//                Network *temp_p=(*array);//append
//                while(temp_p->next!=NULL){
//                    temp_p=temp_p->next;
//                }
//                temp_p->next=temp;
                temp->prev= last;
                last->next=temp;
                last=temp;


            }
            if(temp->transmited_bytes>temp->received_bytes){
                if(*max_number>temp->transmited_bytes ?  0 :( (*max_number)=temp->transmited_bytes ));



            }else{
                if(*max_number>temp->received_bytes ? 0 : ((*max_number)=temp->received_bytes) );
            }

//            temp->next = (*array);//prepend
//            (*array) = temp;
            list_num_size_net++;
        }
        else{
            printf("sscanf error  \n");
            free(temp);
            ret=-1;
            break;
        }
      //  count+=delay;




    }

    printf("count %d \n",count);



    fclose(fp);
    return ret;


}

int memory_read(Memory_list **array){

    FILE *fp;
    char *filename = "memory.data";
    char *p;

    int ret=0;
    int delay=0;
    char buffer[1024]={0};
    __uint64_t  dummy;
    Memory_list * temp=NULL;
    Memory_list * last=NULL;
    if ((fp = fopen(filename, "a+")) == NULL) //create a file if it doesnt exist
        return 1;

    while((fgets(buffer,sizeof(buffer),fp))!=NULL){
        delay=0;
        if(strncmp(buffer,"Time:",5)==0){
            p=strrchr(buffer,'D');
            ret= sscanf(p,"Delay %d",&delay);
            if(fgets(buffer,1024,fp)==NULL){
                ret=-1;
                break;
            }

            if (buffer[0]=='\n'){
                if(fgets(buffer,sizeof(buffer),fp)==NULL){
                    ret=-1;
                    break;
                }
            }

        }
        temp = (Memory_list *) calloc(1, sizeof(Memory_list));
        if (temp == NULL) {
            printf("calloc error %d \n", errno);
            free(temp);
            ret=-1;
            break;
        }
        temp->next=NULL;
        temp->delay_time=delay;
        if(sscanf(buffer,"total memory %" SCNu64 " memory_used %" SCNu64 " memory_free %" SCNu64 " swap_total " "%" SCNu64 " "
                "swap_used %" SCNu64 " ",
                  &temp->memory_total
                ,&temp->memory_used
                ,&dummy
                ,&temp->swap_total
                ,&temp->swap_used
        )==5){
            if((*array)==NULL){
                (*array) = temp;
                last=temp;
            }
            else{
//                Memory_list *temp_p=(*array);//append
//                while(temp_p->next!=NULL){
//                    temp_p=temp_p->next;
//                }
//                temp_p->next=temp;
                temp->prev= last;
                last->next=temp;
                last=temp;



            }


//            temp->next = (*array);//prepend
//            (*array) = temp;
            list_num_size_memory++;
        }
        else{
            printf("sscanf error  \n");
            free(temp);
            ret=-1;
            break;
        }
        //  count+=delay;




    }




    fclose(fp);
    return ret;

}
int interrupts_read(Interrupts_List **array) {


    FILE *fp;
    char *filename = "interrupts.data";
    char *p;

    int ret = 0;
    int delay = 0;
    char buffer[1024] = {0};

    Interrupts_List *temp_list = NULL;
    Interrupts_List *last_list = NULL;

    Interrupts_elements *temp = NULL;
    Interrupts_elements *last = NULL;



    if ((fp = fopen(filename, "r")) == NULL) //open file for reading
        return 1;


    while (fgets(buffer, sizeof(buffer), fp) != NULL ) {
        delay = 0;
        if (strncmp(buffer, "Time:", 5) == 0) {
            p = strrchr(buffer, 'D');
            ret = sscanf(p, "Delay %d", &delay);



        }
        temp_list = (Interrupts_List *) calloc(1, sizeof(Interrupts_List));
        if (temp_list == NULL) {
            printf("calloc error %d \n", errno);
            free(temp_list);
            ret = -1;
            break;
        }
        if ((*array) == NULL) {
            (*array) = temp_list;

            last_list = temp_list;

        } else {
            temp_list->prev=last_list;
            last_list->next=temp_list;
            last_list=temp_list;


        }



    temp_list->next = NULL;
    temp_list->delay_time = delay;
    temp_list->max_number = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL/* && strncmp(fp->_IO_read_ptr,"Time:",5)!=0*/) {

        temp = (Interrupts_elements *) calloc(1, sizeof(Interrupts_elements));
        if (temp == NULL) {
            printf("calloc error %d \n", errno);

            free(temp);
            ret = -1;
            break;
        }
        if (sscanf(buffer, " \n %3s %" SCNu64 " %" SCNu64 " %" SCNu64 " %" SCNu64 " %s %s %s %s \n",
                   temp->interrupts.irq,
                   &temp->interrupts.CPU0,
                   &temp->interrupts.CPU1,
                   &temp->interrupts.CPU2,
                   &temp->interrupts.CPU3,
                   temp->interrupts.ime1,
                   temp->interrupts.ime2,
                   temp->interrupts.ime3,
                   temp->interrupts.ime4
        ) >= 5) {
            if(temp_list->pointer==NULL){
                temp_list->pointer=temp;
                temp_list->pointer->next=NULL;
                temp_list->pointer->prev=NULL;
                last=temp;

            }else{
                temp->prev= last;
                last->next=temp;
                last=temp;
            }
            if (temp_list->max_number < temp->interrupts.CPU0) {

                temp_list->max_number = temp->interrupts.CPU0;
            }
            if (temp_list->max_number <= temp->interrupts.CPU1) {

                temp_list->max_number = temp->interrupts.CPU1;
            }
            if (temp_list->max_number <= temp->interrupts.CPU2) {

                temp_list->max_number = temp->interrupts.CPU2;
            }
            if (temp_list->max_number <= temp->interrupts.CPU3) {

                temp_list->max_number = temp->interrupts.CPU3;
            }

         //   printf("max number %"PRIu64"\n",temp_list->max_number);
        } else {
            printf("sscanf error  \n");
            free(temp);
            ret = -1;
            break;
        }



        if(strncmp(fp->_IO_read_ptr,"Time:",5)==0){
            break;
        }
    }
        list_size_interrupts++;

}




    printf("list size interrupts %d \n",list_size_interrupts);

    fclose(fp);
    return ret;
}