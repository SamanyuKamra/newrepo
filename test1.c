#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int fd1;

    char * myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);

    char strings[100], send[10];
    int curr = 1;

    while (curr < 50)
    {
        
        fd1 = open(myfifo,O_RDONLY);
        read(fd1, strings , 100);

        printf("\nStrings received from P1\n%s", strings);
        close(fd1);

        curr += 5;
        char ind[5];
        sprintf(ind,"%d",curr);
	    strcpy(send,ind);

        printf("Highest index has been sent back to P1\n");

        fd1 = open(myfifo,O_WRONLY);
        write(fd1, send, strlen(send)+1);
        close(fd1);

    }

    return 0;
    
}
