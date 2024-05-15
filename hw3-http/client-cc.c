#include "http.h"

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define  BUFF_SZ 1024

char recv_buff[BUFF_SZ];

char *generate_cc_request(const char *host, int port, const char *path){
	static char req[512] = {0};
	int offset = 0;
	
    //note that all paths should start with "/" when passed in
	offset += sprintf((char *)(req + offset),"GET %s HTTP/1.1\r\n", path);
	offset += sprintf((char *)(req + offset),"Host: %s\r\n", host);
	offset += sprintf((char *)(req + offset),"Connection: Close\r\n");
	offset += sprintf((char *)(req + offset),"\r\n");

	printf("DEBUG: %s", req);
	return req;
}


void print_usage(char *exe_name){
    fprintf(stderr, "Usage: %s <hostname> <port> <path...>\n", exe_name);
    fprintf(stderr, "Using default host %s, port %d  and path [\\]\n", DEFAULT_HOST, DEFAULT_PORT); 
}

int process_request(const char *host, uint16_t port, char *resource){
    int sock;
    int total_bytes = 0;
    char  recv_buff[BUFF_SZ] ;
    char send_buf[BUFF_SZ];
    char  recv_data[BUFF_SZ*4];
    sock = socket_connect(host, port);
    int ret = 0;
    if(sock < 0) return sock;



    //TODO:   Implement Send/Receive loop for Connection:Closed
    //generate request 
    strncpy(send_buf,generate_cc_request(host,port,resource),BUFF_SZ);
    
    //send request to server
    if ((ret=send(sock,send_buf,strlen(send_buf),0)) < 0) {
        perror("send");
        exit(EXIT_FAILURE);
    }

    //confirm that the length of the generated request is equal to the one that was sent.
    if (ret != strlen(send_buf)){
        printf("%d bytes Generated :%d bytes sent\n",ret,strlen(send_buf));
    }


    //recv the data
    while((ret=recv(sock,recv_buff,BUFF_SZ,0)) > 0){
        printf("%.*s", ret, recv_buff);
        if (strlen(recv_data)+ret < (BUFF_SZ*4)){ 
            strncpy(recv_data+total_bytes,recv_buff,ret);
        }
        total_bytes += ret;
        memset(recv_buff,0,BUFF_SZ) ;
    }
    
    printf("\nTotal Bytes: %d\n",total_bytes);
    close(sock);
    return total_bytes;
}

int main(int argc, char *argv[]){
    time_t start = time(NULL);
    char sta[100],sto[100];
    int sock;

    const char *host = DEFAULT_HOST;
    uint16_t   port = DEFAULT_PORT;
    char       *resource = DEFAULT_PATH;
    int        remaining_args = 0;

    // Command line argument processing should be all setup, you should not need
    // to modify this code
    if(argc < 4){
        print_usage(argv[0]);
        //process the default request
        process_request(host, port, resource);
	} else {
        host = argv[1];
        port = atoi(argv[2]);
        resource = argv[3];
        if (port == 0) {
            fprintf(stderr, "NOTE: <port> must be an integer, using default port %d\n", DEFAULT_PORT);
            port = DEFAULT_PORT;
        }
        fprintf(stdout, "Running with host = %s, port = %d\n", host, port);
        remaining_args = argc-3;
        for(int i = 0; i < remaining_args; i++){
            resource = argv[3+i];
            fprintf(stdout, "\n\nProcessing request for %s\n\n", resource);
            process_request(host, port, resource);
        }
    }
    time_t stop = time(NULL);
   // lstart = localtime_r
    strftime(sta,sizeof(sta),"%H:%M:%S %Z",localtime(&start));
    strftime(sto,sizeof(sto),"%H:%M:%S %Z",localtime(&stop));
    double time_elapsed = difftime(stop,start);
    printf("\n\nStart: %s\nStop: %s \nTime Taken: %.f\n",sta,sto,time_elapsed );
}