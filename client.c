#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


void main(){
    char buf[1024];
    int buf_rv = 0;
    int sock_in, sock_out, i;
    struct sockaddr_in addr;
    fd_set readfds;

    sock_in = socket(AF_INET, SOCK_STREAM, 0);
    sock_out = socket(AF_INET, SOCK_STREAM, 0);
    if ((sock_in < 0) || (sock_out < 0))
    {
        perror("socket creation error");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(sock_in, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("socket_in connect error");
        exit(2);
    }
    if(connect(sock_out, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("socket_out connect error");
        exit(2);
    }
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    FD_SET(sock_in, &readfds);
    while(1){
        for(i=0; i<=sock_in; i++){
            select(sock_in+1, &readfds, NULL, NULL, NULL);
            if (FD_ISSET(0, &readfds)){
                buf_rv = read(0, buf, sizeof(buf));
                write(1, buf, buf_rv);
                memset(buf, 0, buf_rv);
            }
            if (FD_ISSET(sock_in, &readfds)){
                buf_rv = read(sock_in, buf, sizeof(buf));
                write(1, buf, buf_rv);
                memset(buf, 0, buf_rv);
            }
        }
    }

}



