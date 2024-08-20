#include <iostream>
#include "log.hpp"

int main() {
    Log log;
    if (log.create_log("log.in")) {
        std::cout << "The Log file has been opened successfully\n";
        while (log.next()) {
            std::cout << "Line=: " << log.line() << std::endl;
            std::cout << "Level=: " << log.level() << std::endl;
            std::cout << "Reformatted=: " << log.reformat() << std::endl;
        }
    } else {
        std::cerr << "Could not open log file\n";
    }
    return 0;
}
