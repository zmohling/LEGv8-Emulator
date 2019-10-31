CC=gcc
ECHO=echo
LINT=cpplint
RM=rm -rvf
MKDIR=mkdir -p
CD=cd
INSTALL=install

# Binary name
BIN=legv8emul

# Directories 
DEST_DIR=/
ROOT_DIR=.
LIB_DIR=$(ROOT_DIR)/lib
SRC_BASE_DIR=$(ROOT_DIR)/src
SRC_SUB_DIRS=$(sort $(dir $(wildcard $(SRC_BASE_DIR)/*/)))
INSTALL_DIR=usr/local/bin

# Generated directories
BUILD_DIR=$(ROOT_DIR)/build

# Libaries
LIBS=$(shell find $(LIB_DIR) -name '*.a')

# Include
INC_DIRS=$(SRC_BASE_DIR)
INC_FLAGS=$(foreach d, $(INC_DIRS), -I$d)

# Compilation and linking flags
DEBUG_FLAGS=-Wall -ggdb3 -Og -D DEBUG_MODE
RELEASE_FLAGS=-O3
C_FLAGS=$(INC_FLAGS) $(DEBUG_FLAGS)
LD_FLAGS=

ifeq ($(shell uname -s),Darwin)
	C_HEADER_DIR=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk
	C_FLAGS += -I$(C_HEADER_DIR)/usr/include/machine/
endif

# Sources, objects, and dependencies
C_SRC=$(shell find $(SRC_BASE_DIR) -name '*.c')
OBJ=$(patsubst %.c, $(BUILD_DIR)/%.o, $(filter %.c,$(subst /, , $(C_SRC))))
DEP=$(OBJ:%.o=%.d)

all: $(BIN)

$(BIN): $(OBJ)
	@$(ECHO) Linking compiled files... 
	@$(CC) $^ -o $(@F) $(LD_FLAGS)

-include $(DEP)

$(BUILD_DIR)/%.o: $(SRC_SUB_DIRS)%.c | $(BUILD_DIR)
	@$(ECHO) Compiling $<
	@$(CC) $(C_FLAGS) -MMD -c $< -o $@

.PHONY: clean lint install uninstall
clean:
	@$(ECHO) Removing all generated files and executables...
	@$(RM) $(BUILD_DIR) $(BIN) *.txt *.mp4 core vgcore.* valgrind*

install:
	@$(ECHO) "Installing to $(DEST_DIR)$(INSTALL_DIR)"
	@$(INSTALL) $(BIN) $(DEST_DIR)$(INSTALL_DIR)

uninstall:
	@$(RM) $(DEST_DIR)$(INSTALL_DIR)/$(BIN)

# Directory generation
$(BUILD_DIR):
	@$(MKDIR) $(BUILD_DIR)
