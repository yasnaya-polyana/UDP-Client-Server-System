#pragma once
#include <iostream>
#include <string>
#include <fstream>


class Log {
private:
    std::ifstream logFile;
    std::string   logLine;
    
public:
     Log(); // Constructor
    ~Log(); // Deconstuctor
    bool create_log(const std::string& filename);
    bool next();
    std::string line();
    std::string level();
    std::string reformat();
};
