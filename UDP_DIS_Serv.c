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
#define SERVER_ADDR "192.168.92.129"

int main()  
{ 
    int sockfd; 
    char buffer[MAXLINE]; 
    struct sockaddr_in servaddr, cliaddr;           

    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr));      

    servaddr.sin_family = AF_INET;  
    servaddr.sin_addr.s_addr = inet_addr(SERVER_ADDR); 
    servaddr.sin_port = htons(PORT);       

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } else { 
        printf("\nSuccessfully created DATAGRAM socket\n"); 
    } 

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } else { 
        printf("\nLocal Port Bound Successfully!!\n"); 
    }        

    int len, n;     
    while (1) { 
        len = sizeof(cliaddr);    
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len); 
        buffer[n] = '\0'; 
        printf("\nData Received : %s", buffer); 
    }    

    return 0; 
}
