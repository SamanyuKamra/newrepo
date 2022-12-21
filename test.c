#include<sys/shm.h>
#include <semaphore.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/ipc.h>

struct timespec a1;

int min(int x, int y)
{
    if(x>y)
    {
        return y;
    }
    else{
        return x;
    }
}

int main()
{
    clock_gettime(CLOCK_REALTIME,&a1);
    int i = 0;
    int j = 0;

    int random;
    char str_2[5];
    char arr[50][5];

    for(i = 0; i<50; i++)
    {
        for(j=0; j<4; j++)
        {
            random = rand()%26 + 65;
            str_2[j] = (char)(random);

        }
        str_2[5] = '\0';
	    strcpy(arr[i], str_2);
    }
    printf("P1: The contents of the array are\n");
    for (i = 0; i<50; i++){
        printf("%s\n", arr[i]);
    }

    char* temp = (char*)malloc(sizeof(arr[0]));
    key_t passwd = ftok("SharedMemory",50);
    int id = shmget(passwd,1024,0666|IPC_CREAT);
    temp = (char*) shmat(id,NULL,0);

    for(int a=0;a<50;)
    {
        int d = a;
        while(d<min(a+5,50))
        {
            strcpy(temp,arr[d]);
            while(strcmp(*&temp,"waiting")!=0){}
            d++;
        }
        a=d;
        printf("Maximum id received by p1: %d\n",a-1);
    }
    return 0;

}
					
