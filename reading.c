//
// Created by dushn on 16.11.20..
//


#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include "reading.h"


int cpu_read(Cpu_list **array) {


    FILE *fp;
    char *filename = "cpu.data";
    char buffer[1024];
    char *p;
    Cpu_list *temp=NULL;
    int ret=0;
    int delay;
    if ((fp = fopen(filename, "r")) == NULL) //create a file if it doesnt exist
        return -1;




    while((fgets(buffer,sizeof(buffer),fp))!=NULL){
        delay=0;
        if(strncmp(buffer,"Time:",5)==0){
            p=strchr(buffer,'D');
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
    *max_number=100;

    if ((fp = fopen(filename, "r")) == NULL) //create a file if it doesnt exist
        return -1;


    while((fgets(buffer,sizeof(buffer),fp))!=NULL){
        delay=0;
        if(strncmp(buffer,"Time:",5)==0){
            p=strchr(buffer,'D');
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
            }
            else{
                Network *temp_p=(*array);//append
                while(temp_p->next!=NULL){
                    temp_p=temp_p->next;
                }
                temp_p->next=temp;


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
        count+=delay;




    }

    printf("count %d \n",count);



    fclose(fp);
    return ret;


}