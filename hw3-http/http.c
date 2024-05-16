#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>

#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>

#include "http.h"

//---------------------------------------------------------------------------------
// TODO:  Documentation
//
// Note that this module includes a number of helper functions to support this
// assignment.  YOU DO NOT NEED TO MODIFY ANY OF THIS CODE.  What you need to do
// is to appropriately document the socket_connect(), get_http_header_len(), and
// get_http_content_len() functions. 
//
// NOTE:  I am not looking for a line-by-line set of comments.  I am looking for 
//        a comment block at the top of each function that clearly highlights you
//        understanding about how the function works and that you researched the
//        function calls that I used.  You may (and likely should) add additional
//        comments within the function body itself highlighting key aspects of 
//        what is going on.
//
// There is also an optional extra credit activity at the end of this function. If
// you partake, you need to rewrite the body of this function with a more optimal 
// implementation. See the directions for this if you want to take on the extra
// credit. 
//--------------------------------------------------------------------------------

char *strcasestr(const char *s, const char *find)
{
	char c, sc;
	size_t len;

	if ((c = *find++) != 0) {
		c = tolower((unsigned char)c);
		len = strlen(find);
		do {
			do {
				if ((sc = *s++) == 0)
					return (NULL);
			} while ((char)tolower((unsigned char)sc) != c);
		} while (strncasecmp(s, find, len) != 0);
		s--;
	}
	return ((char *)s);
}

char *strnstr(const char *s, const char *find, size_t slen)
{
	char c, sc;
	size_t len;

	if ((c = *find++) != '\0') {
		len = strlen(find);
		do {
			do {
				if ((sc = *s++) == '\0' || slen-- < 1)
					return (NULL);
			} while (sc != c);
			if (len > slen)
				return (NULL);
		} while (strncmp(s, find, len) != 0);
		s--;
	}
	return ((char *)s);
}

/* 
    This function takes in the destination host address/ domain name(and resolves the domain name) and the destination port
    converts the destination port into network byte-order and creates a socket to handle the connection. 
    A connection to the remote host is created utilizing the socket created and the active socket is returned
    to be utilized to send the HTTP Requests.
*/
int socket_connect(const char *host, uint16_t port){
    // creating the required variables and structs to create the required socket connection to the server
    struct hostent *hp;
    struct sockaddr_in addr;
    int sock;

    // Translating the hostname, if it is a hostname/domain name rather than an IP address.
    if((hp = gethostbyname(host)) == NULL){
		herror("gethostbyname");
		return -2;
	}
    
    /* - Here we copy the IP address into the list of 
    - The port which is a two byte integer (uint16_t) is also converted to network byte order (aka big-endian) in order for proper interpretation at the destination host
    - The IP address family is set to be IPv4
    - The socket is created in the "sock" variable utilizing "PF_INET", which stands for Protocol Family but contains the same value as AF_INET as seen here : 
    https://github.com/torvalds/linux/blob/master/include/linux/socket.h#L249 
    t notes that we will be using IPv4 Ip addresses to communicate over the socket(aka communication domain)
    - SOCK_STREAM here signifies that we will be using the reliable TCP protocol for communication
    */
	bcopy(hp->h_addr_list[0], &addr.sin_addr, hp->h_length);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	sock = socket(PF_INET, SOCK_STREAM, 0); 

    // if the socket cannot be created/or failed to be created. return
	if(sock == -1){
		perror("socket");
		return -1;
	}

    /* Create connection over the socket to the destination host, given 
    the local socket created, the struct containing the IPv4 address and tcp port to transmit traffic to
    */
    if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
		perror("connect");
		close(sock);
        return -1;
	}

    // return the active socket to be used to make HTTP requests.                                                                                                                                                                                                                                                                   
    return sock;
}

// TODO: 
/*
This function takes in a buffer containing and HTTP Response and the size of the buffer.
The strnstr helper function is used to find the location of the "\r\n\r\n"  which signifies the end of the HTTP header and the position is stored in "end_ptr"
If the location is found the header length is calculated by but subtracting the pointer to the start of http buffer from the pointer to the location of the end_ptr (which is a pointer within the same stream)
hence given you the size of the header outside of the double carriage return and newline combo, and then the size of the "\r\n\r\n"  to the result of the subtraction to get the full size of the http header
The function then returns the length of the header
*/
int get_http_header_len(char *http_buff, int http_buff_len){
    char *end_ptr;
    int header_len = 0;
    end_ptr = strnstr(http_buff,HTTP_HEADER_END,http_buff_len);

    if (end_ptr == NULL) {
        fprintf(stderr, "Could not find the end of the HTTP header\n");
        return -1;
    }

    header_len = (end_ptr - http_buff) + strlen(HTTP_HEADER_END);

    return header_len;
}

/* 
This function also takes in a buffer containing the HTTP Response and the size of the header calculated in the previous function. The aim is to look through the HTTP Header to find 
the "Content-Length" key to guide then number of recv calls later on. 
- The while loop runs until we get to the end of the header as end_header_buff should point to the final position of "\r\n\r\n"  hence signifying that the whole HTTP Header has been traversed
- As the loop runs through using the fact that each Header line ends with "\r\n" each line is checked to see if "Content-Length" is there
- When the correct line is found the line is split using ":" and the right side of the split is converted to an integer and then returned
*/
int get_http_content_len(char *http_buff, int http_header_len){
    char header_line[MAX_HEADER_LINE];

    char *next_header_line = http_buff;
    char *end_header_buff = http_buff + http_header_len;

    while (next_header_line < end_header_buff){
        //seems similar to doing a memset to clear the headerline
        bzero(header_line,sizeof(header_line));

        // splits line by line given that the '\r\n' is used das a line delimeter in the HTTP Header
        sscanf(next_header_line,"%[^\r\n]s", header_line);

        //char *isCLHeader2 = (char *) strcasecmp(header_line,CL_HEADER);
        // searches for "Content-Length" within the line ignoring the case of the string
        char *isCLHeader = strcasestr(header_line,CL_HEADER);
        if(isCLHeader != NULL){
            //locate the ":" in the current line and using the pointer to that retrieve the value after it by incrementing by 1
            // convert the retrieve value to and integer and return.
            char *header_value_start = strchr(header_line, HTTP_HEADER_DELIM);
            if (header_value_start != NULL){
                char *header_value = header_value_start + 1;
                int content_len = atoi(header_value);
                return content_len;
            }
        }
        next_header_line += strlen(header_line) + strlen(HTTP_HEADER_EOL);
    }
    fprintf(stderr,"Did not find content length\n");
    return 0;
}

//This function just prints the header, it might be helpful for your debugging
//You dont need to document this or do anything with it, its self explanitory. :-)
void print_header(char *http_buff, int http_header_len){
    fprintf(stdout, "%.*s\n",http_header_len,http_buff);
}

//--------------------------------------------------------------------------------------
//EXTRA CREDIT - 10 pts - READ BELOW
//
// Implement a function that processes the header in one pass to figure out BOTH the
// header length and the content length.  I provided an implementation below just to 
// highlight what I DONT WANT, in that we are making 2 passes over the buffer to determine
// the header and content length.
//
// To get extra credit, you must process the buffer ONCE getting both the header and content
// length.  Note that you are also free to change the function signature, or use the one I have
// that is passing both of the values back via pointers.  If you change the interface dont forget
// to change the signature in the http.h header file :-).  You also need to update client-ka.c to 
// use this function to get full extra credit. 
//--------------------------------------------------------------------------------------
int process_http_header(char *http_buff, int http_buff_len, int *header_len, int *content_len){
/*    int h_len, c_len = 0;
    h_len = get_http_header_len(http_buff, http_buff_len);
    if (h_len < 0) {
        *header_len = 0;
        *content_len = 0;
        return -1;
    }
    c_len = get_http_content_len(http_buff, http_buff_len);
    if (c_len < 0) {
        *header_len = 0;
        *content_len = 0;
        return -1;
    }

    *header_len = h_len;
    *content_len = c_len;
*/
    char * next = http_buff;
    char header_line[MAX_HEADER_LINE];
/*    char * end_ptr = strnstr(http_buff,HTTP_HEADER_END,http_buff_len);

    if (end_ptr != NULL){
        *header_len = (end_ptr - http_buff) + strlen(HTTP_HEADER_END);
    }else{
        fprintf(stderr, "Could not find the end of the HTTP header\n"); 
    }
 */  

    size_t test = sizeof(HTTP_HEADER_END);

    memset(header_line,0,MAX_HEADER_LINE);
   // char *isCLHeader = strcasestr(header_line,CL_HEADER);

    while (strncmp(next,HTTP_HEADER_EOL,strlen(HTTP_HEADER_EOL)) != 0){
        sscanf(next,"%[^\r\n]s", header_line);
        char *isCLHeader = strcasestr(header_line,CL_HEADER);
        if (isCLHeader != NULL){
                char *header_value_start = strchr(header_line, HTTP_HEADER_DELIM);

                char *header_value = header_value_start + 1;
                *content_len = atoi(header_value); 
        }
        *header_len += strlen(header_line) + strlen(HTTP_HEADER_EOL);
        next += strlen(header_line) + strlen(HTTP_HEADER_EOL);
    }
    *header_len += strlen(HTTP_HEADER_EOL);
    return 0; //success
}

void show_time_elapsed(struct timeval start, struct timeval stop){

    char sta[99],sto[100];
    strftime(sta,sizeof(sta),"%H:%M:%S",localtime(&(start.tv_sec)));
    strftime(sto,sizeof(sto),"%H:%M:%S",localtime(&(stop.tv_sec)));
    double time_elapsed = difftime(stop.tv_sec,start.tv_sec);
    printf("\n\nStart: %s.%ld \nStop: %s.%ld \nTime Taken(secs): %.f\n",sta,start.tv_usec/999,sto,stop.tv_usec/1000,time_elapsed ); 
}