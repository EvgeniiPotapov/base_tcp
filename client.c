#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>



void main(int argc, char *argv[]){
    char buf[1024];
    int buf_rv = 0;
    int i, sock;
    struct sockaddr_in addr;
    fd_set readfds;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket creation error");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = inet_addr(argv[1]);
   
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("socket connect error");
        exit(2);
    }
    while(1){
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);
        FD_SET(sock, &readfds);
        select(sock+1, &readfds, NULL, NULL, NULL);
        
            if (FD_ISSET(0, &readfds)){
                buf_rv = read(0, buf, sizeof(buf));
                send(sock, buf, buf_rv, 0);
                memset(buf, 0, buf_rv);
            }
            if (FD_ISSET(sock, &readfds)){
                buf_rv = recv(sock, buf, sizeof(buf), 0);
                write(1, buf, buf_rv);
                memset(buf, 0, buf_rv);
            }
        
    }

}
