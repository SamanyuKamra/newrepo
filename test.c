#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t forks[5];

void eat(int n){
    printf("Thread %d is eating now\n",n);
}

void take_left(int n){

    printf("Thread %d is trying to pick left fork\n",n);
    sem_wait(&forks[n]);
    printf("Thread %d picks the left fork\n",n);
}

void take_right(int n){

    printf("Thread %d is trying to pick right fork\n",n);
    sem_wait(&forks[(n+1)%5]);
    printf("Thread %d picks the right fork\n",n);

}


void * collect_fork(void * n){

    while (1)
    {
        int thread=*(int *)n;

        if(thread==4){

            take_right(thread);
            take_left(thread);

        }else{

            take_left(thread);
            take_right(thread);
        }

        eat(thread);
        //sleep(2);
        printf("Thread %d has finished eating\n",thread);
        
        sem_post(&forks[(thread+1)%5]);
        printf("Thread %d left right fork\n",thread);
        sem_post(&forks[(thread)]);
        printf("Thread %d leaves left fork\n",thread);

    }
    
    
}

int main(){

    pthread_t thread[5];
    int thread_no[5];

    for(int i = 0 ; i<5 ; i++)
        sem_init(&forks[i],0,1);

    for(int i = 0 ; i<5 ; i++){

        thread_no[i]=i;
        pthread_create(&thread[i],NULL,collect_fork,(void *)&thread_no[i]);

    }

    for(int i=0;i<5;i++)
        pthread_join(thread[i],NULL);

    return 0;
}
