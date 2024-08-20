CC = clang++
LD = clang++
CPPFLAGS = -std=c++17  -I./include 

LDFLAGS = -lpthread

ROOTDIR = ./

CP = cp
ECHO = echo

BUILD_DIR = build

CPP_SOURCES = ./src/log.cpp
CPP_HEADERS = ./src/log.hpp
C_SOURCES = NONE

APP_TESTER = app_tester 

APP = app
LOGAPP = logapp

# Adding test file here
TESTERS_SOURCES = ./src/log_test.cpp
# location of simpletest.cpp
TEST_MODULE = ./simpletest/simpletest.cpp


OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
UNITTEST_OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(TESTERS_SOURCES:.cpp=.o)))
SUB_MODULE_OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(TEST_MODULE:.cpp=.o)))


vpath %.cpp $(sort $(dir $(CPP_SOURCES)))
vpath %.cpp src

$(BUILD_DIR)/%.o: %.cpp $(CPP_HEADERS) Makefile | $(BUILD_DIR)
	$(ECHO) compiling $<
	$(CC) -c $(CPPFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(ECHO) compiling $<
	clang -c $(CFLAGS) $< -o $@

all: $(BUILD_DIR) $(BUILD_DIR)/$(APP)  $(BUILD_DIR)/$(LOGAPP)

#we need to incoporate the testapp to carry out unit tests.
testapp: $(BUILD_DIR) $(BUILD_DIR)/$(APP_TESTER) $(BUILD_DIR)/$(APP_TESTER)

run: $(BUILD_DIR)/$(APP)
	$(BUILD_DIR)/$(APP)

# another app to carry out the test on developed classes
runlogApp: $(BUILD_DIR)/$(LOGAPP)
	$(BUILD_DIR)/$(LOGAPP)	


runtestapp: $(BUILD_DIR)/$(APP_TESTER)
	$(BUILD_DIR)/$(APP_TESTER)


$(BUILD_DIR)/$(APP): main.cpp $(OBJECTS) Makefile
	$(ECHO) linking $<
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $@ ./src/main.cpp $(OBJECTS)
	$(ECHO) successs

$(BUILD_DIR)/$(LOGAPP): main2.cpp $(OBJECTS) Makefile
	$(ECHO) linking app 2 $<
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $@ ./src/main2.cpp $(OBJECTS)
	$(ECHO) logapp successsfully compiled

# We need to Compile simpletest.cpp to get simpletest.o
$(BUILD_DIR)/simpletest.o: $(TEST_MODULE) Makefile | $(BUILD_DIR)
	$(CC) -c $(CPPFLAGS) $< -o $@

$(BUILD_DIR)/$(APP_TESTER): $(UNITTEST_OBJECTS) $(OBJECTS) $(BUILD_DIR)/simpletest.o Makefile
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $@ $(UNITTEST_OBJECTS) $(OBJECTS) $(BUILD_DIR)/simpletest.o


$(BUILD_DIR):
	mkdir $@

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)/$(APP) $(BUILD_DIR)/$(LOGAPP) $(BUILD_DIR)/$(APP_TESTER) $(BUILD_DIR)/*.o
#######################################
# dependencies
#######################################
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

.PHONY: clean all

