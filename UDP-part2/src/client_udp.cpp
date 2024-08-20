#include <iostream>
#include <util.hpp>
#include <iot/socket.hpp>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    // Set client IP address
    uwe::set_ipaddr("192.168.1.7");

    const int server_port = 8877;
    const char* server_name = "192.168.1.8";

    // Socket address used for the server
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET; // IPv4 address

    // Create binary representation of server name and store it as sin_addr
    inet_pton(AF_INET, server_name, &server_address.sin_addr);

    // htons: port in network order format
    server_address.sin_port = htons(server_port);

    // Create a UDP socket
    uwe::socket sock{AF_INET, SOCK_DGRAM, 0};

    // Port for the client
    const int client_port = 1001;

    // Socket address used for the client
    struct sockaddr_in client_address;
    memset(&client_address, 0, sizeof(client_address));
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(client_port);
    inet_pton(AF_INET, uwe::get_ipaddr().c_str(), &client_address.sin_addr);

    // Bind the socket to the client address
    sock.bind((struct sockaddr *)&client_address, sizeof(client_address));

    // Data that will be sent to the server
    std::string message = "This is an IOT packet";

    // Send data to the server
    int len = sock.sendto(
        message.c_str(), message.length(), 0,
        (sockaddr*)&server_address, sizeof(server_address));

    // Receive echoed message from the server
    char buffer[800];
    memset(buffer, 0, sizeof(buffer));
    struct sockaddr_in received_from;
    socklen_t received_from_len = sizeof(received_from);
    size_t addrlen = received_from_len; // Ensure addrlen is of type size_t
    len = sock.recvfrom(buffer, sizeof(buffer), 0, (sockaddr*)&received_from, &addrlen);
    if (len > 0) {
        std::cout << "Received from server: " << buffer << std::endl;
    }

    return 0;
}

