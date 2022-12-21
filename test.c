#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>


#define PORT 8080

int main()
{	
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	
	char arr[51][10];

	for(int i = 1; i<51 ; i++){
		char s[10] = "string";
		char no[5];
		sprintf(no,"%d",i);
		strcat(s,no);
		strcpy(arr[i],s);
	
	}	
	
	int addrlen = sizeof(address);
	char ind[10] = {0};
	char send_data[100];
	
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	
	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

	int curr = 1;

	while(curr<50){

		strcat(arr[curr],"\n");

		for(int i = curr+1 ; i<= curr+4 ; i++){

			strcat(arr[curr],arr[i]);
			strcat(arr[curr],"\n");	
		}

		strcpy(send_data, arr[curr]);
		
		send(new_socket , send_data , strlen(send_data) , 0 );

		printf("Stirngs sent form p1\n");

		valread = read( new_socket , ind, 10);
		curr = atoi(ind);
			
		printf("Highest index returned form p2:-%d\n", curr);

	}

	return 0;

}
