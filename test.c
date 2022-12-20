#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

sem_t sauce[2];
sem_t forks[5];
pthread_mutex_t waiter;

int getBowl(){
    int x = 0;
    while(i<2){
        int semTemp = -1;
        int error = sem_getvalue(&sauce[x] , &semTemp);
        if(semTemp == 1)
        {
            sem_wait(&sauce[x]);
            return (x);
        }
        x++;
    }

}

void eat(int philosphers, int bowls)
{
    printf("Philosopher %d eating in Bowl %d with forks %d and %d\n", philosphers,bowls, philosphers, (philosphers + 1) % 5);
    usleep(500000);
    sem_post(&forks[philosphers]);
    sem_post(&forks[(philosphers + 1) % 5]);
    sem_post(&sauce[bowls]);

}
void getforks(int philosphers)
{
    sem_wait(&fork[philosphers]);
    sem_wait(&forks[(philosphers + 1) % 5]);

}
void *philospherThinking(void *i)
{
    int philosphers = *((int *)i);
    while(true)
    {
        pthread_mutex_lock(&waiter);
        getforks(philosphers);
        int bowls = getBowl();
        pthread_mutex_unlock(&waiter);
        eat(philosphers, bowls);

    }
}
int main(){
    pthread_t DP[5];
    int i[5] = {0,1,2,3,4};
    pthread_mutex_init(&waiter, NULL);
    int j = 0;
    while(j<5) //Forks
    {
        sem_init(&forks[j],0,1);
        j++;
    }
    int k = 0;
    while (k<2)
    {
        sem_init(&sauce[k],0,1);
    }
    for (int a = 0; a < 5; a++)
    {
        if (pthread_create(&DP[a], NULL, philospherThinking, &i[a]) == -1)
        {
            printf("error creating pthread\n");
        }
    }
    for(int a = 0; a<5;a++){
        pthread_join(DP[a], NULL);
    }
    return 0;

}
