#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT 8080 
#define MAXLINE 100 
#define CLIENT_ADDR "192.168.92.129" 

int main()  
{ 
    int sockfd; 
    char buffer[MAXLINE]; 
    struct sockaddr_in servaddr, cli_addr; 

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } else { 
        printf("\nSuccessfully created socket!!!"); 
    }     

    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr(CLIENT_ADDR);       

    int n, len;    

    do {  
        printf("\n\nEnter a string to send to SERVER . . . "); 
        scanf("%s", buffer); 
        sendto(sockfd, buffer, strlen(buffer) + 1, 0, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
        printf("Message Sent to server : %s", buffer);        
    } while (strcmp(buffer, "quit")); 

    printf("\n\n"); 
    close(sockfd); 
    return 0; 
}
