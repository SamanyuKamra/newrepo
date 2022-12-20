#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int fd;

    char * myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);

    char arr1[80], arr2[80];

    char arr[51][10];

    for(int i = 1; i<51 ; i++){

        char s[10] = "string";
        char no[5];
        sprintf(no,"%d",i);
        strcat(s,no);
        strcpy(arr[i],s);
    }

    int curr = 1;
    char receive[5];
    char send[100];

    while (curr < 50)
    {
        fd = open(myfifo, O_WRONLY);

        strcat(arr[curr],"\n");

        for(int i = curr+1 ; i<= curr+4 ; i++){

            strcat(arr[curr],arr[i]);
            strcat(arr[curr],"\n");	

	    }
        printf("\nMessage has been sent to p2\n");
        strcpy(send,arr[curr]);

        write(fd, send, strlen(send)+1);
        close(fd);

        fd = open(myfifo, O_RDONLY);

        read(fd, receive, sizeof(receive));
        curr = atoi(receive);

        printf("\nIndex received from P2 %d\n", curr);

        close(fd);

    }
    return 0;
}
