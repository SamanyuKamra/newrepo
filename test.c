#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
sem_t forks[5];
sem_t sauceBowls[4];
pthread_mutex_t waiter;
void getForks(int philosopherArrived)
{
    sem_wait(&forks[philosopherArrived]);
    sem_wait(&forks[(philosopherArrived + 1) % 5]);
}
int getBowl()
{
    for (int i = 0; i < 4; i++)
    {
        int semValue = -1;
        int err = sem_getvalue(&sauceBowls[i], &semValue);
        if (semValue == 1)
        {
            sem_wait(&sauceBowls[i]);
            return (i);
        }
    }
}
void eat(int philosopherArrived, int bowlAcquired)
{
    printf("Philosopher %d eating in Bowl %d with forks %d and %d\n", philosopherArrived,
           bowlAcquired, philosopherArrived, (philosopherArrived + 1) % 5);
    usleep(500000);
    sem_post(&forks[philosopherArrived]);
    sem_post(&forks[(philosopherArrived + 1) % 5]);
    sem_post(&sauceBowls[bowlAcquired]);
}
void *philosopherAction(void *philosopherIndex)
{
    int philosopherArrived = *((int *)philosopherIndex);
    while (1)
    {
        pthread_mutex_lock(&waiter);
        getForks(philosopherArrived);
        int acquiredBowl = getBowl();
        pthread_mutex_unlock(&waiter);
        eat(philosopherArrived, acquiredBowl);
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
    //creating bowls
    for (int i = 0; i < 4; i++)
    {
        sem_init(&sauceBowls[i], 0, 1);
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
