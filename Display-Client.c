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
#define CLIENT_ADDR "192.168.117.129"
#define CLIENT_PORT 15678

int main() {
    int sd;
    struct sockaddr_in serv_addr, cli_addr;

    bzero((char*) &cli_addr, sizeof(cli_addr));
    bzero((char*) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    serv_addr.sin_port = htons(SERVER_PORT);

    cli_addr.sin_family = AF_INET;
    cli_addr.sin_addr.s_addr = inet_addr(CLIENT_ADDR);
    cli_addr.sin_port = htons(CLIENT_PORT);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    printf("\nSuccessfully created stream socket");

    bind(sd, (struct sockaddr*)&cli_addr, sizeof(cli_addr));
    printf("\nLocal Port Bound Successfully!!");

    connect(sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    printf("\nConnected Successfully!!");

    close(sd);
}