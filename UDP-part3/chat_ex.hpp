#pragma once

#include <stdint.h>

#include <string>
#include <cstring>
#include <arpa/inet.h>

#define MAX_USERNAME_LENGTH 64
#define MAX_MESSAGE_LENGTH 1024

// Server always run on this port
#define SERVER_PORT 8867

namespace chat { 

/**
 * @brief Chat protocol command types 
 * @var chat_type::JOIN
 * Client join server message
 * @var chat_type::JACK
 * Client ACK in reply to JOIN
 * @var chat_type::BROADCAST
 * Client sends message to all online users
 * @var chat_type::DIRECTMESSAGE
 * Client sends message to particlar user
 * @var chat_type::LIST
 * Client request list of current online users
 * Server sends list of current online users (might be multiple of these terminated with user END)
 * @var chat_type::LEAVE
 * Client requests to leave
 * Server sents to all online users that particular user has left
 * @var chat_type::LACK
 * Server sends in response to LEAVE
 * @var chat_type::EXIT
 * Client sends message to terminate server and all online clients
 * Server sends to all online users informing them to terminate
 * @var chat_type::ERROR
 * Server sends to client if an error has occured
 * 
*/
enum chat_type {
    JOIN = 0,
    JACK,
    BROADCAST,
    DIRECTMESSAGE,
    LIST,
    LEAVE,
    LACK,
    EXIT,
    CREATE_GROUP,
    GROUP,
    ERROR,
    UNKNOWN,
};

/** @brief check if type is indeed a valid chat_type.
 * @param type the command type to check
 * @return true if a valid type, otherwise false
*/
inline bool is_valid_type(chat_type type) {
    return type >= JOIN && type <= ERROR;   
}

/** 
 * @struct chat_message
 * @brief Representation of chat protocol message
 * @var chat_message::type_
 *  Member 'type_' contains the chat command
 * @var chat_message::username_
 *  Member 'username_' the messages associated username
 * @var chat_message::message_
 *  Member 'message_' the message body
 */
struct chat_message {
    uint8_t type_;
    int8_t username_[MAX_USERNAME_LENGTH];
    int8_t message_[MAX_MESSAGE_LENGTH];
};

/**
 * @brief Create a JOIN message
 * @param username to be stored in the message
 * @return the chat message
*/
inline chat_message join_msg(std::string username) {
    chat_message msg;
    msg.type_ = JOIN;
    memcpy(&msg.username_[0], username.c_str(), username.length());
    msg.username_[username.length()] = '\0';
    msg.message_[0] = '\0';
    return msg;
}

/**
 * @brief Create a JACK message

 * @return the chat message
*/
inline chat_message jack_msg() {
    return chat_message{JACK, '\0', '\0'};
}

/**
 * @brief Create a BROADCAST message
 * @param username to be stored in the message
 * @param message to be stored in the message
 * @return the chat message
*/
inline chat_message broadcast_msg(std::string username, std::string message) {
    chat_message msg{BROADCAST, '\0', '\0'};
    memcpy(&msg.username_[0], username.c_str(), username.length());
    msg.username_[username.length()] = '\0';
    memcpy(&msg.message_[0], message.c_str(), message.length());
    msg.message_[message.length()] = '\0';
    return msg;
}

/**
 * @brief Create a DIRECTMESSAGE message
 * @param username to be stored in the message
 * @param message to be stored in the message
 * @return the chat message
*/
inline chat_message dm_msg(std::string username, std::string message) {
    chat_message msg{DIRECTMESSAGE, '\0', '\0'};
    memcpy(&msg.username_[0], username.c_str(), username.length());
    msg.username_[username.length()] = '\0';
    memcpy(&msg.message_[0], message.c_str(), message.length());
    msg.message_[message.length()] = '\0';
    return msg;
}

//##########################################################################
/**
 * @brief Create a GROUP message 
 * @param group_name to be stored in the message
 * @param message to be stored in the message
 * @return the chat message
*/


inline chat_message create_group_msg(std::string group_name, std::string message) { //function to create group chat 
    chat_message msg;
    msg.type_=CREATE_GROUP; //set message type to create group.
    msg.username_[0]= '\0'; //group chat does not require username 

    std::size_t group_name_length = std::min(group_name.length(), static_cast<size_t>(MAX_MESSAGE_LENGTH) - 1);
    memcpy(&msg.message_[0], group_name.c_str(), group_name_length);
    msg.message_[group_name_length] = '\0';
    
    return msg;
}

//##########################################################################

/**
 * @brief Create a LIST message
 * @param username to be stored in the message
 * @param message to be stored in the message
 * @return the chat message
*/
inline chat_message list_msg(std::string username = "", std::string message = "") {
    chat_message msg{LIST, '\0', '\0'};
    memcpy(&msg.username_[0], username.c_str(), username.length());
    msg.username_[username.length()] = '\0';
    memcpy(&msg.message_[0], message.c_str(), message.length());
    msg.message_[message.length()] = '\0';
    return msg;
}

/**
 * @brief Create a LEAVE message
 * @return the chat message
*/
inline chat_message leave_msg() {
    return chat_message{LEAVE, '\0', '\0'};
}

/**
 * @brief Create a LACK message
 * @return the chat message
*/
inline chat_message lack_msg() {
    return chat_message{LACK, '\0', '\0'};
}

/**
 * @brief Create a EXIT message
 * @return the chat message
*/
inline chat_message exit_msg() {
    return chat_message{EXIT, '\0', '\0'};
}

/**
 * @brief Create a ERROR message
 * @param err code
 * @return the chat message
*/
inline chat_message error_msg(uint16_t err) {
    chat_message msg{ERROR, '\0'};
    *((int *)(&msg.message_[0])) = htons(err);
    return msg;
}

/**
 * @brief Print a chat message to stdout
 * @param message to be printed
*/
void print_message(chat_message message);

#define ERR_USER_ALREADY_ONLINE 0
#define ERR_UNKNOWN_USERNAME    1
#define ERR_UNEXPECTED_MSG      2

}; // namespace chat
