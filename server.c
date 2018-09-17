#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>


void main(){
    int sock_out, sock_in, listener, i,buf_rv;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;
    fd_set readfds;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int enable = 1;
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) < 0)
    perror("setsockopt(SO_REUSEPORT) failed");
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }
    
    listen(listener, 2);
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

    /*while(1)
    {
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    FD_SET(sock_in, &readfds);
    select(sock_in+1, &readfds, NULL, NULL, NULL);
    
        if (FD_ISSET(0, &readfds)){
            buf_rv = read(0, buf, sizeof(buf));
            send(sock_out, buf, buf_rv, 0);
            memset(buf, 0, buf_rv);
            }
        if (FD_ISSET(sock_in, &readfds)){
            buf_rv = recv(sock_in, buf, sizeof(buf), 0);
            write(1, buf, buf_rv);
            memset(buf, 0, buf_rv);
            }
        

    }*/
    close(0);
    dup(sock_in);
    close(1);
    dup(sock_out);
    execl("./sftp-server", "sftp-server");
}
