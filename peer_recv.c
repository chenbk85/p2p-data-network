#include "peer_recv.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "util.h"

udp_handler handler;

int init_udp (int port)
{
    struct sockaddr_in sin, sender;
    int sock_fd, slen, recv_len;
    //initialize an input buffer
    char * buf = (char *)malloc(BUFFLEN * sizeof(char));
    if (buf == 0)
        error("Buffer failed to initialize.");

    slen = sizeof(sender);
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock_fd < 0)
        error("Socket failed to initialize.");
	//clear and set the ip addresses
    memset((char *) &sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
	//bind the socket
    if (bind(sock_fd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
        error("Socket failed to bind.");
	//receive packets in a loop

	printf("Starting receive loop.\r\n");

    while (1)
    {
        recv_len = recvfrom(sock_fd, buf, BUFFLEN, RECV_FLAGS, (struct sockaddr *)&sender, &slen);
        if (recv_len < 0)
            error("Function recvfrom() failed.");
        printf("Received packet.");
    }

    return 1;
}
