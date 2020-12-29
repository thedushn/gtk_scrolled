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

                temp->prev= last;
                last->next=temp;
                last=temp;


            }

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
    return ret<0 ? -1 : 0;

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

                temp->prev= last;
                last->next=temp;
                last=temp;


            }
            if(temp->transmited_bytes>temp->received_bytes){
                if(*max_number>temp->transmited_bytes ?  0 :( (*max_number)=temp->transmited_bytes ));



            }else{
                if(*max_number>temp->received_bytes ? 0 : ((*max_number)=temp->received_bytes) );
            }


            list_num_size_net++;
        }
        else{
            printf("sscanf error  \n");
            free(temp);
            ret=-1;
            break;
        }





    }

    printf("count %d \n",count);



    fclose(fp);
    return ret<0 ? -1 : 0;


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

                temp->prev= last;
                last->next=temp;
                last=temp;



            }



            list_num_size_memory++;
        }
        else{
            printf("sscanf error  \n");
            free(temp);
            ret=-1;
            break;
        }





    }




    fclose(fp);
    return ret<0 ? -1 : 0;

}
int interrupt_list_read(Interrupts_List **array,FILE *fp,char buffer_r[512]){

    char buffer[512] = {0};

    list_size_interrupts++;

    Interrupts_List *temp_list = NULL;



    Interrupts_elements *temp = NULL;

    char *p;

    int delay = 0;
    temp_list = (Interrupts_List *) calloc(1, sizeof(Interrupts_List));
    if (temp_list == NULL) {
        printf("calloc error %d \n", errno);
        free(temp_list);
        return -1;

    }
    if ((*array) == NULL) {
        (*array) = temp_list;



    } else {
        Interrupts_List *temp_p=(*array);
                while(temp_p->next!=NULL){
                    temp_p=temp_p->next;
                }
        temp_list->prev= temp_p;
        temp_p->next=temp_list;



    }
    if (strncmp(buffer_r, "Time:", 5) == 0) {
        p = strrchr(buffer_r, 'D');
        if(sscanf(p, "Delay %d", &delay)<1){
            free(temp_list);
            return -1;
        }


    }
    else{
        free(temp_list);
        return -1;
    }
    temp_list->next = NULL;
    temp_list->delay_time = delay;
    temp_list->max_number = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL ) {
        if (strncmp(buffer, "Time:", 5) != 0) {

            return interrupt_element_read(&temp_list,fp,buffer);
        }
        else{
            while(temp_list->pointer){
                temp=temp_list->pointer;
                temp_list->pointer=temp_list->pointer->next;
                free(temp);
            }
            free(temp_list);
            temp_list=NULL;
            return -1;
        }


    }





    return 0;
}
int interrupt_element_read(Interrupts_List **array,FILE *fp,char buffer_r[512]){

    char buffer[512];

    Interrupts_List *temp_list = *array;


    Interrupts_elements *temp = NULL;
    Interrupts_elements *last = NULL;
    temp = (Interrupts_elements *) calloc(1, sizeof(Interrupts_elements));
    if (temp == NULL) {
        printf("calloc error %d \n", errno);

        free(temp);
       return -1;
    }

    if (( sscanf(buffer_r, "%3s %" SCNu64 " %" SCNu64 " %" SCNu64 " %" SCNu64 " %s %s %s %s",
                      temp->interrupts.irq,
                      &temp->interrupts.CPU0,
                      &temp->interrupts.CPU1,
                      &temp->interrupts.CPU2,
                      &temp->interrupts.CPU3,
                      temp->interrupts.ime1,
                      temp->interrupts.ime2,
                      temp->interrupts.ime3,
                      temp->interrupts.ime4
    ) > 2)) {
        if (temp_list->pointer == NULL) {
            temp_list->pointer = temp;
            temp_list->pointer->next = NULL;
            temp_list->pointer->prev = NULL;
            last = temp;

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


    } else {
        printf("sscanf error  \n");
        printf("buffer %s\n", buffer_r);
        free(temp);
        return -1;
    }


    while (fgets(buffer, sizeof(buffer), fp) != NULL) {

        if (strncmp(buffer, "Time:", 5) == 0){
            if(interrupt_list_read(array,fp,buffer)!=0){
                return -1;
            }
            return 0;

        }
        temp = (Interrupts_elements *) calloc(1, sizeof(Interrupts_elements));
        if (temp == NULL) {
            printf("calloc error %d \n", errno);

            free(temp);
          return -1;
        }
        if (( sscanf(buffer, "%3s %" SCNu64 " %" SCNu64 " %" SCNu64 " %" SCNu64 " %s %s %s %s",
                          temp->interrupts.irq,
                          &temp->interrupts.CPU0,
                          &temp->interrupts.CPU1,
                          &temp->interrupts.CPU2,
                          &temp->interrupts.CPU3,
                          temp->interrupts.ime1,
                          temp->interrupts.ime2,
                          temp->interrupts.ime3,
                          temp->interrupts.ime4
        ) > 2)) {
            if (temp_list->pointer == NULL) {
                temp_list->pointer = temp;
                temp_list->pointer->next = NULL;
                temp_list->pointer->prev = NULL;
                last = temp;

            } else {
                temp->prev = last;
                last->next = temp;
                last = temp;
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


        } else {
            printf("sscanf error  \n");
            printf("buffer %s\n", buffer);
            free(temp);
            if (strncmp(buffer, "Time:", 5) != 0) {
                printf("buffer %s\n", buffer);

                return -1;
            }

            return -1;
        }


    }
    return 0;
}
int interrupts_read(Interrupts_List **array) {


    FILE *fp;
    char *filename = "interrupts.data";


    int ret = 0;

    char buffer[512] = {0};





    if ((fp = fopen(filename, "r")) == NULL) //open file for reading
        return -1;


    while (fgets(buffer, sizeof(buffer), fp) != NULL ) {

        if (strncmp(buffer, "Time:", 5) == 0) {



           if(interrupt_list_read(array,fp,buffer)!=0 ? (ret=-1): ( ret=0) );


        }
        else{
            printf("buffer %s\n",buffer);

            ret=-1;
            break;
            }

}




    printf("list size interrupts %d \n",list_size_interrupts);

    fclose(fp);
    return ret<0 ? -1 : 0;
}
int device_read(Device_List **array){

    FILE *fp;
    char *filename = "device.data";


    int ret = 0;

    char buffer[512] = {0};





    if ((fp = fopen(filename, "r")) == NULL) //open file for reading
        return -1;


    while (fgets(buffer, sizeof(buffer), fp) != NULL ) {

        if (strncmp(buffer, "Time:", 5) == 0) {



            if(device_list_read(array,fp,buffer)!=0 ? (ret=-1): ( ret=0) );


        }
        else{
            printf("buffer %s\n",buffer);

            ret=-1;
            break;
        }

    }






    fclose(fp);
    return ret<0 ? -1 : 0;

}
int device_list_read(Device_List **array,FILE *fp,char buffer_r[512]){

    char buffer[512] = {0};



    Device_List *temp_list = NULL;



    D_Collection *temp = NULL;

    char *p;

    int delay = 0;
    temp_list = (Device_List *) calloc(1, sizeof(Device_List));
    if (temp_list == NULL) {
        printf("calloc error %d \n", errno);
        free(temp_list);
        return -1;

    }
    if ((*array) == NULL) {
        (*array) = temp_list;



    } else {
        Device_List *temp_p=(*array);
        while(temp_p->next!=NULL){
            temp_p=temp_p->next;
        }
        temp_list->prev= temp_p;
        temp_p->next=temp_list;



    }
    if (strncmp(buffer_r, "Time:", 5) == 0) {
        p = strrchr(buffer_r, 'D');
        if(sscanf(p, "Delay %d", &delay)<1){
            free(temp_list);
            return -1;
        }


    }
    else{
        free(temp_list);
        return -1;
    }
    temp_list->next = NULL;
    temp_list->delay_time = delay;
    temp_list->device_num = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL ) {
        if (strncmp(buffer, "Time:", 5) != 0) {

            return device_element_read(&temp_list,fp,buffer);
        }
        else{
            while(temp_list->pointer){
                temp=temp_list->pointer;
                temp_list->pointer=temp_list->pointer->next;
                free(temp);
            }
            free(temp_list);
            temp_list=NULL;
            return -1;
        }


    }





    return 0;
}
int device_element_read(Device_List **array,FILE *fp,char buffer_r[512]){

    char buffer[512];

    Device_List *temp_list = *array;


    D_Collection *temp = NULL;
    D_Collection *last = NULL;
    temp = (D_Collection *) calloc(1, sizeof(D_Collection));
    if (temp == NULL) {
        printf("calloc error %d \n", errno);

        free(temp);
        return -1;
    }

    if ((  sscanf(buffer_r,"Devices %s available %"  SCNu64 "  free %"  SCNu64 " type %s directory %s used %"  SCNu64 ""
            " total %"  SCNu64 "\n",
            temp->devices.name,
            &temp->devices.avail,
            &temp->devices.free,
            temp->devices.type,
            temp->devices.directory,
            &temp->devices.used,
            &temp->devices.total
    ) > 2)) {
        if (temp_list->pointer == NULL) {
            temp_list->pointer = temp;
            temp_list->pointer->next = NULL;
            temp_list->pointer->prev = NULL;
            last = temp;

        }




    } else {
        printf("sscanf error  \n");
        printf("buffer %s\n", buffer_r);
        free(temp);
        return -1;
    }
    temp_list->device_num++;



    while (fgets(buffer, sizeof(buffer), fp) != NULL) {

        if (strncmp(buffer, "Time:", 5) == 0){
            if(device_list_read(array,fp,buffer)!=0){
                return -1;
            }
            printf("%d\n",temp_list->device_num);
            return 0;

        }
        temp = (D_Collection *) calloc(1, sizeof(D_Collection));
        if (temp == NULL) {
            printf("calloc error %d \n", errno);

            free(temp);
            return -1;
        }
        if ((  sscanf(buffer,"Devices %s available %"  SCNu64 "  free %"  SCNu64 " type %s directory %s used %"  SCNu64 ""
                              " total %"  SCNu64 "\n",
                      temp->devices.name,
                      &temp->devices.avail,
                      &temp->devices.free,
                      temp->devices.type,
                      temp->devices.directory,
                      &temp->devices.used,
                      &temp->devices.total
        ) > 2)) {
            if (temp_list->pointer == NULL) {
                temp_list->pointer = temp;
                temp_list->pointer->next = NULL;
                temp_list->pointer->prev = NULL;
                last = temp;

            } else {
                temp->prev = last;
                last->next = temp;
                last = temp;
            }
            temp->devices.checked=false;



        } else {
            printf("sscanf error  \n");
            printf("buffer %s\n", buffer);
            free(temp);
            if (strncmp(buffer, "Time:", 5) != 0) {
                printf("buffer %s\n", buffer);

                return -1;
            }

            return -1;
        }
        temp_list->device_num++;


    }

    return 0;
}