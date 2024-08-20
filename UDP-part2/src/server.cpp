    #include <iostream>
    #include <iot/socket.hpp>
    #include <util.hpp>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>


int main() {


// ##########   The first thing to do is to configure the server  ##########
// Just as we did for the client, we need to specify an IP address and port number for the server,
//allowing the socket to determine the message's destination,
// and it must conform to network byte order formatting. 
    uwe::set_ipaddr("192.168.1.8"); // we set the server IP address
    char buffer[800]; //let us provide sizeable memory as buffer to hold the message from client
    const int Server_port = 8877;
   // socket address utilized for the server or Receiver
    struct sockaddr_in the_server_addr; // this structure will hold server address
    memset(&the_server_addr, 0, sizeof(the_server_addr));
    the_server_addr.sin_family = AF_INET;
    the_server_addr.sin_port = htons(Server_port);
    inet_pton(AF_INET, uwe::get_ipaddr().c_str(), &the_server_addr.sin_addr);

    // Inn creating the UDP socket, identified by the SOCK_DGRAM parameter,
    // we are utilizing AF_INET to represent an IPv4 address:
    uwe::socket sock{AF_INET, SOCK_DGRAM, 0};
   

    sock.bind((struct sockaddr *)&the_server_addr, sizeof(the_server_addr));
    size_t bufferlen = sizeof(buffer);

  // ##########  let us now configure the client  ##########
    const int client_port = 1001;
    const char* the_client_name = "192.168.1.7";
    sockaddr_in the_client_addr; // data structure for keeping IPv4 or IPv6 addresses
     // Now that the socket is prepared to send messages, it needs to be bound to the client's address:
    size_t the_client_addr_len = sizeof(the_client_addr);
	memset(&the_client_addr, 0, sizeof(the_client_addr));
    memset(buffer, 0, sizeof(buffer));
	the_client_addr.sin_family = AF_INET; // IPv4 address
	// creates a binary representation of the server name and stores it as sin_addr
	inet_pton(AF_INET, the_client_name, &the_client_addr.sin_addr);

  
    the_client_addr.sin_port = htons(client_port); /* this converts the port into network order format*/



     // ##########  let us now receive data from the client  ##########
    // We need to wait for the data to be received from the client.
    std::cout << " waiting for messages from the client ...\n";
    memset(&the_client_addr, 0, sizeof(the_client_addr)); // preparing the address buffer
    sock.recvfrom (buffer, sizeof(buffer), 0, (sockaddr*)&the_client_addr, &the_client_addr_len);

    //##########  let us display the received data from the client  ##########
    // Upon waiting for and receiving data from the client, we should show
    // the received message alongside the receiver's IP address:
    --bufferlen; // we need to reserve a memory space for terminating NULL -> '\0'
    buffer[bufferlen] = '\0';  // terminating the buffer with NULL to signify end of the message
    printf("received: '%s' from client %s\n", buffer, inet_ntoa(the_client_addr.sin_addr));
    return 0;
}


