#include <iostream>
#include <fstream>
#include <string>
#include "log.hpp"


Log::Log() {}

Log::~Log() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

bool Log::create_log(const std::string& logfilename) {
    bool file_is_opened;
    logFile.open(logfilename);
    file_is_opened = logFile.is_open();
    return file_is_opened;
}




bool Log::next() {
    std::string logLine;
    if (std::getline(logFile, logLine)) {
        return true;
    } 
    else {
        return false;
    }
}

std::string Log::line(void) {
    return logLine;
}

std::string Log::level() {
    std::string currentLine;
    
    if (std::getline(logFile, logLine)) {
        size_t startPos = logLine.find('[');

        size_t endPos = logLine.find(']', startPos);

        if (startPos != std::string::npos && endPos != std::string::npos) {
            
            return logLine.substr(startPos + 1, endPos - startPos - 1);
        } else {
            return ""; 
        }
    } else {
        return ""; 
    }
}

std::string Log::reformat() {
    std::string logLine;

    if (std::getline(logFile, logLine)) {
        size_t startPos = logLine.find('[');
        size_t endPos = logLine.find(']', startPos);

        if (startPos != std::string::npos && endPos != std::string::npos) {
            std::string logLevel = logLine.substr(startPos + 1, endPos - startPos - 1);

            std::string logMessage = logLine.substr(endPos + 1);
            
            return logMessage + " (" + logLevel + ")";
        } else {
            return logLine; 
        }
    } else {
        return "";
    }
}

