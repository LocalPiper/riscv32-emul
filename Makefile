CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude -g

SRC_DIR := src
BUILD_DIR := build
BIN := $(BUILD_DIR)/riscvemu

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

all: $(BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: all
	$(BIN)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run

