#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

sem_t forks[5];
void eat(int phi)
{
    printf("Philosopher %d is eating.\n",phi);
    sleep(3);
    printf("Philosopher %d has finished eating.\n",phi);

}


void *getPhil(void * n)
{
    int phi = *(int *)n;
    int f1;
    int f2;
    if(phi ==4)
    {
        f2 = 4;
        f1 = 0;
    }
    else{
        f1 = phi;
        f2 = phi + 1;
    }

    for(int i =0;i<10;i++)
    {
        sem_wait(&forks[f1]);
        printf("Philosopher %d has picked up fork %d\n",phi,f1);
        sem_wait(&forks[f2]);
        printf("Philosopher %d has picked up fork %d\n",phi,f2);

        eat(phi);

        sem_post(&forks[f2]);
        printf("Philosopher %d has put down fork %d\n",phi,f2);
        sem_post(&forks[f1]);
        printf("Philosopher %d has put down fork %d\n",phi,f1);
    }

    printf("Philosopher %d is full.\n",phi);

}

int main()
{
    int arr[5];
    pthread_t DP[5];
    int j = 0;
    while (j<5)
    {
        sem_init(&forks[j],0,1);
        j++;
    }
    printf("Dinner has commenced\n");
    for(int x=0;x<5;x++){
		pthread_create(&DP[x],NULL,getPhil,(void *)&x);
	}

	for(int a=0;a<5;a++){
		pthread_join(DP[a],NULL);
    }

    printf("Dinner has been concluded. All Philosophers have eaten and there was no deadlock.\n");
    
}
