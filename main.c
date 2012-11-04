#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>

#include "peer_recv.h"
#include "util.h"

#define CHORD_COMM "1597"

void comm_handler (int);

/*
 *
 */
int main(int argc, char** argv) {
	struct addrinfo local;
    int sockfd;

	init_listener(CHORD_COMM, comm_handler, &local);
	printf("passed listener\n");

    return (EXIT_SUCCESS);
}

void comm_handler (int sock_fd)
{
    char buffer[64];
    read(sock_fd, buffer, 64);
    printf("%s\n", buffer);
    close(sock_fd);
}
