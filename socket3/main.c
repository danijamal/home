
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include "tree.h"

#define BUFFER_SIZE 1024



int socket_connect(char *host, in_port_t port){
    struct hostent *hp;
    struct sockaddr_in addr;
    int on = 1, sock;
    int sock_check = 0;
    int con_check = 0;

    do{
    if((hp = gethostbyname(host)) == NULL){
            herror("gethostbyname");
            exit(1);
    }
    bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));

    sock_check = sock;
    con_check = connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    }while(con_check == -1 && sock_check == -1 );
        
    return sock;
}
 
int main(int argc, char *argv[]){
	
    int fd, u=0;
    char buffer[BUFFER_SIZE];
    long long number;

    FILE* output=fopen("file.txt" , "a");
    node_t* root=NULL;
    
    
    while(u < 10){
        fd = socket_connect( "srvn.ddns.net", 80);
        write(fd, "GET /misc/rand.php\r\n", strlen("GET /misc/rand.php\r\n")); 
        bzero(buffer, BUFFER_SIZE);

        while(read(fd, buffer, BUFFER_SIZE - 1) != 0){
                fprintf(stderr, "%s\n", buffer);
                number = (int)atoi(buffer);
                root = insertNode(root, number);
                bzero(buffer, BUFFER_SIZE);
        }
        shutdown(fd, SHUT_RDWR); 
        close(fd); 
        u++;
    }
    
    printf("\n");
    inorderWrite(output, root);
    
   
    printf("\n- - - - T R E E - - - - \n\n");
    inorderPrint(root);

    fclose(output);;
    return 0;
}