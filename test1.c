#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int file_add;
    struct timespec a2;
    
    char fifo_add[20] = "helloo";

    while(1){
        char inp[2000];
        file_add = open(fifo_add, O_RDONLY);
        read(file_add, inp, 2000);
        close(file_add);

        //Printing stuff
        int counter;

        char char_id[5];
        int curr_index;

        if (inp[0]=='1'){
            curr_index = inp[1] - '0';
            counter = 2;
        }
        else if (inp[0]=='2'){
            curr_index = 10*(inp[1] - '0') + (inp[2] - '0');
            counter = 3;
        }

        printf("P2: Recieved current index %i\n", curr_index);
        
        int i, j;
        for  (i = 0; i<5; i++){
            printf("P2: Index %d: ",curr_index);
            for (j = 0; j<4; j++){
                printf("%c",inp[counter]);
                counter++;
            }
            printf("\n");
            curr_index++;
        }

        curr_index--;

        char new_id[10];
        sprintf(new_id, "%d", curr_index-1);

        file_add = open(fifo_add, O_WRONLY);
        write(file_add, new_id, strlen(new_id)+1);
        close(file_add);

        printf("P2: Sent current index %i\n", curr_index);

        if (curr_index>48){
            break;
        }
        
    }
    clock_gettime(CLOCK_REALTIME,&a2);
    printf("Exexution time = %f\n",fabs(((a2.tv_sec - a1.tv_sec)+(a2.tv_nsec - a1.tv_nsec))/1e9));

    return 0;
}
