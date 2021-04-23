#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>

int main() {
    // https://man7.org/linux/man-pages/man7/udp.7.html
    // https://man7.org/linux/man-pages/man7/socket.7.html
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    // https://man7.org/linux/man-pages/man2/bind.2.html
    bind(udp_socket, 0, 0); // TODO FIXME

    // TODO https://man7.org/linux/man-pages/man7/epoll.7.html
}