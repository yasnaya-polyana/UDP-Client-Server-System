#include "log.hpp"
#include "../simpletest/simpletest.h"
#include <iostream>

char const * groups[] = {
    "Log",
};

DEFINE_TEST_G(CreateLogTest, Log) {
    Log log;
    bool success = log.create_log("../log.in");
    TEST_MESSAGE(success != true, "Failed to open log!");
}

DEFINE_TEST_G(NextTest, Log) {
    Log log;
    log.create_log("../log.in");
    bool success = log.next();
    TEST_MESSAGE(success == true, "Failed to read log!");
}

DEFINE_TEST_G(LineTest, Log) {
    Log log;
    log.create_log("../log.in");
    log.next();
    std::string line = log.line();
    TEST_MESSAGE(line.compare("Invalid operation") != 0, "Expecting Invalid operation!");
}

DEFINE_TEST_G(LevelTest, Log) {
    Log log;
    log.create_log("../log.in");
    log.next();
    std::string level = log.level();
    TEST_MESSAGE(level.compare("ERROR") != 0, "Expecting ERROR level!");
}

DEFINE_TEST_G(ReformatTest, Log) {
    Log log;
    log.create_log("../log.in");
    log.next();
    std::string reformatted = log.reformat();
    TEST_MESSAGE(reformatted.compare("Invalid operation (ERROR)") != 0, "Expecting reformatted log message!");
}

DEFINE_TEST_G(LogLevelExtractionFailure, Log) {
   //Verify the Failure of Log Level Extraction: 
   //this will confirm that an empty string is generated when no log level is detected within the log line.
    Log log;
    log.create_log("log_without_level.in");
    log.next();
    std::string level = log.level();
    TEST_STR_EQ(level.c_str(), "");
}

int main() {
    bool passed = TestFixture::ExecuteTestGroup("Log", TestFixture::Verbose);
    return passed ? 0 : 1;

}
