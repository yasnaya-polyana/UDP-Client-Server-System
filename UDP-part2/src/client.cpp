
#include <iostream>
#include <iot/socket.hpp>
#include <util.hpp>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>



int main() {

// There is need to specify an IP address and port number for the client,
//allowing the socket to determine the message's destination,
// and it must conform to network byte order formatting. 
// ############################################
	// Let us set the client's IP address:
	uwe::set_ipaddr("192.168.1.7");
	// This is utilized by the socket API to send messages from this device,
	// reflecting our strategy during server code development.


	// Next, we need to create the UDP socket, identified by the SOCK_DGRAM argument,
	// utilizing AF_INET to specify an IPv4 address:
	uwe::socket sock{AF_INET, SOCK_DGRAM, 0};
	/* Now that the socket is prepared for sending messages,
	it needs to be bound to the client's address: */

// ################# Setting up the client  #############################
	const int the_client_port = 1001; // the client's designated port
	struct sockaddr_in client_address; // the socket address used for the client
	memset(&client_address, 0, sizeof(client_address));
	client_address.sin_family = AF_INET;
	client_address.sin_port = htons(the_client_port);
	inet_pton(AF_INET, uwe::get_ipaddr().c_str(), &client_address.sin_addr);
	sock.bind((struct sockaddr *)&client_address, sizeof(client_address));


    // Now, we proceed to set up the server, which acts as the recipient of packets sent by the client
	const int local_server_port = 8877; // this represents the Port the server is expected to use
	const char* local_server_name = "192.168.1.8"; // the IP address of the server
	sockaddr_in local_server_address; // structure for holding IPv4 or IPv6 addresses
	memset(&local_server_address, 0, sizeof(local_server_address));
	local_server_address.sin_family = AF_INET; // IPv4 address

	// The binary representation of the server name is stored as sin_addr
	inet_pton(AF_INET, local_server_name, &local_server_address.sin_addr);
	// htons: port in network order format
	local_server_address.sin_port = htons(local_server_port);
   
	//Now, we move forward to send the message to the server:
	std::string message = "This is an IOT packet"; // this is the data packet that will be sent to our server
	int sent_msg_len = sock.sendto(message.c_str(), message.length(), 0,
	(sockaddr*)&local_server_address, sizeof(local_server_address)); // let us send the data
	std::cout << message.c_str() << " is now sent ...\n";
	return 0;
}





