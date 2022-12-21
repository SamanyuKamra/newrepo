#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
    /*Connect to FIFO*/
    int file_add;

    char fifo_add[20] = "helloo";
    mkfifo(fifo_add, 0666);

    /*To generate an array (of size 50) of strings (of length 4)*/ 
    int i=0, j=0;

    int r_key;
	char str_2[5];
	char arr[50][5];

	for (i = 0; i < 50; i++)
	{
		for (j = 0; j < 4; j++)
		{
			r_key = rand()%26 + 65;
			str_2[j] = (char)(r_key);
		}   
		str_2[5] = '\0';
		strcpy(arr[i], str_2);
	}

    /*Prints the contents of the array*/
    printf("P1: The contents of the array are\n");
    for (i = 0; i<50; i++){
        printf("%s\n", arr[i]);
    }

    

    /*Using FIFO*/
    int first_id = 0;

    
    while (1){
        char str[24]="";

        int flag;
        if (first_id<10){
            flag = 1;
        }
        else{
            flag = 2;
        }

        char char_flag[4];
        sprintf(char_flag, "%d", flag);
        strcat(str, char_flag);

        char char_id[4];
        sprintf(char_id, "%d", first_id);
        strcat(str, char_id);

        strcat(str, arr[first_id]);
        strcat(str, arr[first_id + 1]);
        strcat(str, arr[first_id + 2]);
        strcat(str, arr[first_id + 3]);
        strcat(str, arr[first_id + 4]);
        
        file_add = open(fifo_add, O_WRONLY);
        write(file_add, str, sizeof(str));
        close(file_add);
        
        printf("P1: Sent with index %i\n", first_id);



        char new_id[5];
        int file_add = open(fifo_add, O_RDONLY);
        read(file_add, new_id, 3);
        close(file_add);

        first_id = atoi(new_id);
        first_id++;
        printf("P1: Recieved index %i\n", first_id);

        if (first_id>48){
            break;
        }
        first_id++;        
        
    }


    return 0;
}
