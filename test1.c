#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080

int main()
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;

	char strings[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

	int curr = 1;
	while(curr < 50){

		valread = read( sock , strings, 1024);
		printf("Stirngs received from p1 :- \n");
		printf("%s\n",strings );
		curr+=5;
		char ind[5];
		sprintf(ind,"%d",curr);
		send(sock , ind , strlen(ind) , 0 );
		printf("Highest index sent from p2 to p1\n");
		

	}
	return 0;
}
