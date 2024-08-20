CC = clang++
LD = clang++

CPPFLAGS = -std=c++17 -I/opt/iot/include -D__DEBUG__=1
LDFLAGS = -lpthread -L/opt/iot/lib -liot

ROOTDIR = ./
ECHO = echo
CP = cp

SOURCE_DIR = src
BUILD_DIR = build

# Let's Specify source files for each application
CLIENT_SOURCE_FILE = $(SOURCE_DIR)/client.cpp
SERVER_SOURCE_FILE = $(SOURCE_DIR)/server.cpp

# We are not using Headers yet
CPP_HEADERS = 

APP1 = client
APP2 = server

# Object files for each app
CLIENT_OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(CLIENT_SOURCE_FILE:.cpp=.o)))
SERVER_OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(SERVER_SOURCE_FILE:.cpp=.o)))

vpath %.cpp $(SOURCE_DIR)

all: $(BUILD_DIR) $(BUILD_DIR)/$(APP1) $(BUILD_DIR)/$(APP2)

runCL: $(BUILD_DIR)/$(APP1)
	$(BUILD_DIR)/$(APP1)

runSR: $(BUILD_DIR)/$(APP2)
	$(BUILD_DIR)/$(APP2)

$(BUILD_DIR)/$(APP1): $(CLIENT_OBJECTS)
	$(ECHO) "Linking Clients $@"
	$(CC) $(CLIENT_OBJECTS) $(LDFLAGS) -o $@
	$(ECHO) "The client has been successfully compiled and linked  $@"

$(BUILD_DIR)/$(APP2): $(SERVER_OBJECTS)
	$(ECHO) "Linking Server $@"
	$(CC) $(SERVER_OBJECTS) $(LDFLAGS) -o $@
	$(ECHO) "The Server has been successfully compiled and linked $@"

# Compiling .cpp files to .o
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(CPP_HEADERS) | $(BUILD_DIR)
	$(ECHO) "Compiling codes $<"
	$(CC) $(CPPFLAGS) -c $< -o $@

# Compile client.cpp into client.o
$(BUILD_DIR)/client.o: $(SOURCE_DIR)/client.cpp $(CPP_HEADERS) | $(BUILD_DIR)
	$(ECHO) "Compiling client.cpp"
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	-rm -fR $(BUILD_DIR)/$(APP1) $(BUILD_DIR)/$(APP2) $(BUILD_DIR)/*.o

.PHONY: clean all
