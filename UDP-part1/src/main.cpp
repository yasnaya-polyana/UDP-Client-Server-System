#include <iostream>
#include <string>
#include "log.hpp"  // Include the header file

// Part 1: Get a message from a log line
std::string getMessageFromLog(const std::string& logLine) {
    size_t startPos = logLine.find(": ") + 2;  // Find the position after ": "
    return logLine.substr(startPos);
}

// Part 2: Get the log level from a log line
std::string getLogLevelFromLog(const std::string& logLine) {
    size_t startPos = 1;  // Start from index 1 to skip '['
    size_t endPos = logLine.find("]:");  // Find the end position of log level
    return logLine.substr(startPos, endPos - startPos);
}

// Part 3: Reformat a log line
std::string reformatLogLine(const std::string& logLine) {
    std::string message = getMessageFromLog(logLine);
    std::string logLevel = getLogLevelFromLog(logLine);
    return message + " (" + logLevel + ")";
}

int main() {
    std::string errorLine = "[ERROR]: Invalid operation";
    std::string warningLine = "[WARNING]: File not found";
    std::string infoLine = "[INFO]: Operation completed";

    // Part 1: Get a message from a log line
    std::string errorMessage = getMessageFromLog(errorLine);
    std::string warningMessage = getMessageFromLog(warningLine);
    std::string infoMessage = getMessageFromLog(infoLine);

    // Part 2: Get the log level from a log line
    std::string errorLevel = getLogLevelFromLog(errorLine);
    std::string warningLevel = getLogLevelFromLog(warningLine);
    std::string infoLevel = getLogLevelFromLog(infoLine);

    // Part 3: Reformat a log line
    std::string reformattedErrorLine = reformatLogLine(errorLine);
    std::string reformattedWarningLine = reformatLogLine(warningLine);
    std::string reformattedInfoLine = reformatLogLine(infoLine);

    // Testing
    std::cout << "Error Message: " << errorMessage << std::endl;
    std::cout << "Warning Message: " << warningMessage << std::endl;
    std::cout << "Info Message: " << infoMessage << std::endl;

    std::cout << "Error Level: " << errorLevel << std::endl;
    std::cout << "Warning Level: " << warningLevel << std::endl;
    std::cout << "Info Level: " << infoLevel << std::endl;

    std::cout << "Reformatted Error Line: " << reformattedErrorLine << std::endl;
    std::cout << "Reformatted Warning Line: " << reformattedWarningLine << std::endl;
    std::cout << "Reformatted Info Line: " << reformattedInfoLine << std::endl;

    return 0;
}
