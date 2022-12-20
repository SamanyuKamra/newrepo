#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t forks[5];
sem_t sauce;
int bowls = 2;
void eat(int phi){
    printf("Philosopher %d is eating.\n",phi);
    sleep(4);
    printf("Philosopher %d has finished eating.\n",phi);

}
void * getPhil(void * n){
	int phi=*(int *)n;

    int f1, f2;

    if (phi == 4){
        f1 = 0;
        f2 = 4;
    }
    else{
        f1 = phi;
        f2 = phi + 1;
    }

    int i;
    for (i=0; i<10; i++){
        sem_wait(&sauce);
        printf("Philospher %d has picked up a sauce bowl\n", phi);
        bowls--;
        //print_sauce_bowl();
        sem_wait(&forks[f1]);
        printf("Philosopher %d has picked up fork %d\n",phi,f1);
        sem_wait(&forks[f2]);
        printf("Philosopher %d has picked up fork %d\n",phi,f2);

        eat(phi);

        sem_post(&forks[f2]);
        printf("Philosopher %d has put down fork %d\n",phi,f2);
        sem_post(&forks[f1]);
        printf("Philosopher %d has put down fork %d\n",phi,f1);
        sem_post(&sauce);
        printf("Philospher %d has put down a sauce bowl\n", phi);
        bowls++;
        //print_sauce_bowl();
    }
    printf("Philosopher %d is full.\n",phi);
}
int main()
{
	int i,arr[5];
	pthread_t t_id[5];

    sem_init(&sauce, 0, 2);
	
	for(i=0;i<5;i++){
		sem_init(&forks[i],0,1);
    }
		
	for(i=0;i<5;i++){
		pthread_create(&t_id[i],NULL,getPhil,(void *)&i);
	}

	for(i=0;i<5;i++){
		pthread_join(t_id[i],NULL);
    }

    printf("Dinner has been concluded. All Philosophers have eaten and there was no deadlock.\n");
}
