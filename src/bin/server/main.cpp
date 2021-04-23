#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>



int main() {
    // https://man7.org/linux/man-pages/man7/ipv6.7.html
    // https://man7.org/linux/man-pages/man7/udp.7.html
    // https://man7.org/linux/man-pages/man7/socket.7.html
    int udp_socket = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);

    // https://linux.die.net/man/3/getaddrinfo (works withouth casting and protocol agnostic)

    // https://man7.org/linux/man-pages/man2/bind.2.html
    //bind(udp_socket, &sin6, sizeof(sin6)); // TODO FIXME

    // TODO https://man7.org/linux/man-pages/man7/epoll.7.html
}