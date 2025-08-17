# --------------------------
# Toolchain & project names
# --------------------------

CC        ?= cc
PROJECT   := datastructures

# --------------------------
# Layout (directories)
# --------------------------

# If BUILD_DIR is empty (e.g., overridden from env), default it to 'build'
ifeq ($(strindex $(BUILD_DIR)),)
BUILD_DIR := build
endif

SRC_DIR   := src
INC_DIR   := include
TEST_DIR  := tests
OBJ_DIR   := $(BUILD_DIR)/obj
BIN_DIR   := $(BUILD_DIR)/bin

# --------------------------
# Compiler/linker flags
# --------------------------

CFLAGS   ?= -std=c17 -Wall -Wextra -Werror -O0 -g -I$(INC_DIR)
LDFLAGS  ?=

# --------------------------
# Source discovery & objects
# --------------------------

SRCS       := $(wildcard $(SRC_DIR)/*.c)
OBJS       := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

TEST_SRCS  := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS  := $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))

TEST_BIN   := $(BIN_DIR)/run_tests

# Let make find %.c in both src/ and tests/
vpath %.c $(SRC_DIR) $(TEST_DIR)

# Helper to debug variables: `make print-OBJ_DIR`
print-%:
	@echo $* = $($*)

# --------------------------
# Phony targets
# --------------------------

.PHONY: all test fast-test memcheck asan clean print-%

# Default target
all: $(TEST_BIN)

# --------------------------
# Compilation & linking
# --------------------------

# Single pattern rule: build any obj from a %.c found via vpath
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link final test binary
$(TEST_BIN): $(OBJS) $(TEST_OBJS) | $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

# Create build dirs
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# --------------------------
# Convenience targets
# --------------------------

# Run tests under Valgrind (always memory-check)
test: CFLAGS += -O0 -g
test: $(TEST_BIN)
	valgrind --leak-check=full --show-leak-kinds=all \
	         --errors-for-leak-kinds=all --error-exitcode=1 \
	         $(TEST_BIN)

# Quick run without Valgrind
fast-test: $(TEST_BIN)
	$(TEST_BIN)

# Alias: memcheck behaves the same as test
memcheck: test

# Build & run with AddressSanitizer + UndefinedBehaviorSanitizer
asan: CFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
asan: LDFLAGS += -fsanitize=address,undefined
asan: clean $(TEST_BIN)
	$(TEST_BIN)

# Clean all build artifacts
clean:
	rm -rf $(BUILD_DIR)
