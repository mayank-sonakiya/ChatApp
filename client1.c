// code for client 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/shm.h>
#include"common.h"
#include<pthread.h>

void * thread_function();

struct shared_use_st *shared_stuff;

int main()
{
    pthread_t a_thread;
    void * thread_result;
    void *shared_memory = (void*)0;
    int running = 1,what_to_do;
    int shmid,host;
    char buffer[BUFFER_SZ];
    shmid = shmget((key_t)1234,sizeof(struct shared_use_st), 0666 | IPC_CREAT); //created shared memory
    shared_memory = shmat(shmid, (void*)0, 0); // shared memory attached with shmid
    shared_stuff = (struct shared_use_st *)shared_memory;   
    pthread_create(&a_thread,NULL,thread_function,NULL); //thread create for checking whether data is avalable for reading
    while(1){
        while(shared_stuff->flag == 0){      
            printf("Enter the message\n");
            scanf("%s",buffer);
            strncpy(shared_stuff->message,buffer,BUFFER_SZ);
            printf("Enter the host(2/3/4)\n");
            scanf("%d",&host);     
            shared_stuff->flag = 1;     // if flag == 1 means it represent data is been written and flag ==0 means data has been read now anyone can write
            switch(host){ // host selection 
                case 2:
                    shared_stuff->written_for_2 = 1;
                    break;
                case 3:
                    shared_stuff->written_for_3 = 1;
                    break;
                case 4:
                   shared_stuff-> written_for_4 = 1;
                    break;
                default:
                    printf("no such host\n");
                    break;
            }
         }
       }
    pthread_join(a_thread,thread_result);
}

void *thread_function()    // thread function continuously checking for data available for reading
{
    while(1){
    if(shared_stuff->written_for_1 == 1){
         printf("message : %s\n",shared_stuff->message);
         shared_stuff->flag = 0;
         shared_stuff->written_for_1 = 0;
        sleep(1);
      } 
    }  
    pthread_exit("nice work!");
}
// this is the code for client 3. save this code as client3.c and then compile it using gcc client3.c -o client3 -lpthread

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/shm.h>
#include"common.h"
#include<pthread.h>

void *thread_function();

struct shared_use_st *shared_stuff;

int main()
{
    pthread_t a_thread;
    void *thread_result;
    void *shared_memory = (void*)0;
    int running = 1,what_to_do;
    int shmid,host;
    char buffer[BUFFER_SZ];
    shmid = shmget((key_t)1234,sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    shared_memory = shmat(shmid, (void*)0, 0);
    shared_stuff = (struct shared_use_st *)shared_memory;
    pthread_create(&a_thread,NULL,thread_function,NULL);
     while(running){       

        while(shared_stuff->flag == 0){      
            printf("Enter the message\n");
            scanf("%s",buffer);
            strncpy(shared_stuff->message,buffer,BUFFER_SZ);
            printf("Enter the host(2/1/4)\n");
            scanf("%d",&host);
            shared_stuff->flag = 1;
            switch(host){
                case 2:
                    shared_stuff->written_for_2 = 1;
                    break;
                case 1:
                    shared_stuff->written_for_1 = 1;
                    break;
                case 4:
                   shared_stuff-> written_for_4 = 1;
                    break;
                default:
                    printf("no such host\n");
                    break;
            }
         }
    }
    pthread_join(a_thread,thread_result);
}

void *thread_function()
{
     while(1){
     if(shared_stuff->written_for_3 == 1){
          printf("message : %s\n",shared_stuff->message);
        shared_stuff->flag = 0;
         shared_stuff->written_for_3 = 0;
         sleep(1);
      }
    }
    pthread_exit("nice work!");
 }
 
 /*// this is the code for client 3. save this code as client3.c and then compile it using gcc client4.c -o client4 -lpthread*/
 
 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/shm.h>
#include"common.h"
#include<pthread.h>

void *thread_function();

struct shared_use_st *shared_stuff;

int main()
{   
    pthread_t a_thread;
    void *thread_result;
    void *shared_memory = (void*)0;
    int running = 1,what_to_do;
    int shmid,host;
    char buffer[BUFFER_SZ];
    shmid = shmget((key_t)1234,sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    shared_memory = shmat(shmid, (void*)0, 0);
    shared_stuff = (struct shared_use_st *)shared_memory;
    pthread_create(&a_thread,NULL,thread_function,NULL);
            
    while(1){
        while(shared_stuff->flag == 0){                        
            printf("Enter the message\n");
            scanf("%s",buffer);
            strncpy(shared_stuff->message,buffer,BUFFER_SZ);
            printf("Enter the host(2/1/3)\n");
            scanf("%d",&host);
            shared_stuff->flag = 1;
            switch(host){
                case 2:
                    shared_stuff->written_for_2 = 1;
                    break;
                case 1:
                    shared_stuff->written_for_1 = 1;
                    break;
                case 3:
                   shared_stuff-> written_for_3 = 1;
                    break;
                default:
                    printf("no such host\n");
                    break;
            }
         }
    }
    pthread_join(a_thread,thread_result);
}

void *thread_function()
{
    while(1){
    if(shared_stuff->written_for_4 == 1){
        printf("message : %s\n",shared_stuff->message);
        shared_stuff->flag = 0;
        shared_stuff->written_for_4 = 0;
        sleep(1);
      }
    }
     pthread_exit("nice work!");
}
