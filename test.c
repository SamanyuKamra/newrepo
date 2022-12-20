#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
sem_t forks[5];
pthread_mutex_t waiter;
void getForks(int philosopherArrived)
{
    sem_wait(&forks[philosopherArrived]);
    sem_wait(&forks[(philosopherArrived + 1) % 5]);
}
void eat(int philosopherArrived)
{
    printf("Philosopher %d eating with forks %d and %d\n", philosopherArrived,
           philosopherArrived, (philosopherArrived + 1) % 5);
    usleep(500000);
    sem_post(&forks[philosopherArrived]);
    sem_post(&forks[(philosopherArrived + 1) % 5]);
}
void *philosopherAction(void *philosopherIndex)
{
    int philosopherArrived = *((int *)philosopherIndex);
    while (1)
    {
        pthread_mutex_lock(&waiter);
        getForks(philosopherArrived);
        pthread_mutex_unlock(&waiter);
        eat(philosopherArrived);
    }
}
int main()
{
    pthread_t philosopher[5];
    int philosopherIndex[5] ={0,1,2,3,4};
    pthread_mutex_init(&waiter, NULL);
    //creating forks
    for (int i = 0; i < 5; i++)
    {
        sem_init(&forks[i], 0, 1);
    }
    //creating philosophers as threads
    for (int i = 0; i < 5; i++)
    {
        if (pthread_create(&philosopher[i], NULL, philosopherAction, &philosopherIndex[i]) == -1)
        {
            printf("error creating pthread\n");
        }
    }
    for (int i = 0; i < 5; i++)
    {

        pthread_join(philosopher[i], NULL);
    }

    return 0;
}
