#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <unistd.h>
#include <iostream>

int main() {
    const int BUF_SIZE = 500;
    // https://man7.org/linux/man-pages/man7/ipv6.7.html
    // https://man7.org/linux/man-pages/man7/udp.7.html
    // https://man7.org/linux/man-pages/man7/socket.7.html
    struct addrinfo hints{};
    struct addrinfo *result, *rp;
    int udp_server_fd;
    int s;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t nread;
    char buf[BUF_SIZE];

    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = nullptr;
    hints.ai_addr = nullptr;
    hints.ai_next = nullptr;

   s = getaddrinfo("::", "1337", &hints, &result);
    if (s != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(s) << std::endl;
        exit(EXIT_FAILURE);
    }

   /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully bind(2).
       If socket(2) (or bind(2)) fails, we (close the socket
       and) try the next address. */

   for (rp = result; rp != nullptr; rp = rp->ai_next) {
        udp_server_fd = socket(rp->ai_family, rp->ai_socktype,
                rp->ai_protocol);
        if (udp_server_fd == -1)
            continue;

       if (bind(udp_server_fd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

       close(udp_server_fd);
    }

   if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

   freeaddrinfo(result);           /* No longer needed */

   for (;;) {
        peer_addr_len = sizeof(struct sockaddr_storage);
        nread = recvfrom(udp_server_fd, buf, BUF_SIZE, 0,
                (struct sockaddr *) &peer_addr, &peer_addr_len);
        if (nread == -1)
            continue;               /* Ignore failed request */

       char host[NI_MAXHOST], service[NI_MAXSERV];

       s = getnameinfo((struct sockaddr *) &peer_addr,
                        peer_addr_len, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICSERV);
       if (s == 0)
            printf("Received %ld bytes from %s:%s\n",
                    (long) nread, host, service);
        else
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

       if (sendto(udp_server_fd, buf, nread, 0,
                    (struct sockaddr *) &peer_addr,
                    peer_addr_len) != nread)
            fprintf(stderr, "Error sending response\n");
    }

    // https://linux.die.net/man/3/getaddrinfo (works withouth casting and protocol agnostic)

    // https://man7.org/linux/man-pages/man2/bind.2.html
    //bind(udp_socket, &sin6, sizeof(sin6)); // TODO FIXME

    // TODO https://man7.org/linux/man-pages/man7/epoll.7.html
}