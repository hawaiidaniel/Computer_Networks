#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <sys/wait.h>

#define MYPORT "22159"
#define HOST "127.0.0.1"

int main(void){
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;
	int byte_count;
	socklen_t fromlen;
	char buf[512];
	float k;
    int rv;
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    
    if((rv = getaddrinfo(HOST, MYPORT, &hints, &servinfo)) != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    
    for(p = servinfo; p != NULL; p = p->ai_next){
        if((sockfd = socket(p->ai_family, p->ai_socktype,
                            p->ai_protocol)) == -1){
            perror("serverA: socket");
            continue;
        }
        
        if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1){
            close(sockfd);
            perror("serverA: bind");
            continue;
        }
        
        break;
        
    }
	
	if(p == NULL){
		fprintf(stderr, "serverA failed to bind socket\n");
		return 2;
	}
	
	freeaddrinfo(servinfo);
	printf("The Server A is up and running using UDP on port %s\n",MYPORT);
	
	/*while(1){
		fromlen = sizeof their_addr;
		if((byte_count = recvfrom(sockfd, &k, sizeof buf, 0, 
				(struct sockaddr *)&their_addr, &fromlen)) == -1){
				printf("Error occurs on recvfrom.");
				exit(1);
		}
		
		printf(“The Server A received input <%g>\n",k);
		
		if((byte_count = sendto(sockfd, &(k*k), sizeof buf, 0,
				(struct sockaddr *)&their_addr, &fromlen)) == -1){
				printf("Error occurs on recvfrom.");
				exit(1);
		}
		
		printf("The Server A finished sending the output to AWS.\n");
	}*/
	
	close(sockfd);
	return 0;
}	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	