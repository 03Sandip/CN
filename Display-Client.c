#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define SERVER_ADDR "192.168.117.128"
#define SERVER_PORT 15678

int main() 
{
    int sd, newsd, cli_len, n;
    struct sockaddr_in cli_addr, serv_addr;

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    serv_addr.sin_port = htons(SERVER_PORT);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("Socket creation failed");
        return 1;
    }
    printf("\nSuccessfully created stream socket");

    if (bind(sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }
    printf("\nLocal Port Bound Successfully!!");

    listen(sd, 2);

    while (1) 
    {
        cli_len = sizeof(cli_addr);
        printf("\nWaiting for any Client to connect at server port %u \n", SERVER_PORT);

        newsd = accept(sd, (struct sockaddr*)&cli_addr, &cli_len);
        if (newsd < 0) {
            perror("Accept failed");
            continue;
        }

        printf("\nReceived from Client [IP %s, TCP PORT %d]",
               inet_ntoa(cli_addr.sin_addr),
               ntohs(cli_addr.sin_port));

        close(newsd);
    }

    close(sd);
    printf("\n\n");

    return 0;
}
