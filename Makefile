CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lm
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)

# List of object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.c=$(BUILD_DIR)/%.o)

# Test executable
TEST_EXEC = $(BUILD_DIR)/test

.PHONY: all clean test

all: $(TEST_EXEC)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test source files
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create test executable
$(TEST_EXEC): $(OBJS) $(TEST_OBJS)
	$(CC) $(OBJS) $(TEST_OBJS) -o $@ $(LDFLAGS)

# Run tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -f $(BUILD_DIR)/*.o $(TEST_EXEC)
