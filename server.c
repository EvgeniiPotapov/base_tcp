#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>


void main(){
    int sock_out, sock_in, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 2);
    
    while(1)
    {
        sock_out = accept(listener, NULL, NULL);
        if(sock_out < 0)
        {
            perror("accept");
            exit(3);
        }
        sock_in = accept(listener, NULL, NULL);
        if(sock_in < 0)
        {
            perror("accept");
            exit(3);
        }
        write(sock_out, "Hello\n", 6);
        sleep(4);
        write(sock_out, "Hello\n", 6);

    }
}