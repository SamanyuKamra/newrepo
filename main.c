#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    pid_t pid = fork();
    if (pid>0)
    {
        execl("./test","./test",NULL);
    }
    else{
        execl("./test1","./test1",NULL);
    }
    
    return 0;
}
