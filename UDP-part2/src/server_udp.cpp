#include <iostream>
#include <iot/socket.hpp>
#include <util.hpp>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    // set the server IP address
    uwe::set_ipaddr("192.168.1.8");

    // port to start the server on
    const int server_port = 8877;

    //socket address used for the server
    struct sockaddr_in server_address; // this structure will hold server address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;

    // htons : host to netwrok short: transforms a value into host byte
    // ordering format to a short value in network byte ordering format
    server_address.sin_port = htons(server_port);

    // creates binary representation of server name and stores it as sin_addr
    inet_pton(AF_INET, uwe::get_ipaddr().c_str(), &server_address.sin_addr);

    //create a UDP socket
    uwe::socket sock{AF_INET, SOCK_DGRAM, 0};

    sock.bind((struct sockaddr *)&server_address, sizeof(server_address));

    // let us provide sizeable memory as buffer to hold the message from client
    char buffer[800];

    // We need to wait for the data to be received from the client continually.
    while (true) {
        struct sockaddr_in client_address; // data structure for keeping IPv4 or IPv6 addresses
        size_t client_address_len = sizeof(client_address);
        memset(&client_address, 0, sizeof(client_address));
        memset(buffer, 0, sizeof(buffer));
        
        std::cout << "No Message From The Client..." << std::endl;

        // Receive message from client
        int bytes_received = sock.recvfrom(buffer, sizeof(buffer), 0, (sockaddr*)&client_address, &client_address_len);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            std::cout << "Received message from client " << inet_ntoa(client_address.sin_addr) << ": " << buffer << std::endl;

            // Echo back the received message to the client
            sock.sendto(buffer, bytes_received, 0, (sockaddr*)&client_address, sizeof(client_address));
        }
    }

    return 0;
}