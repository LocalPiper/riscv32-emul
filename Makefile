CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC = main.cpp cpu.cpp memory.cpp instructions.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = riscvemu

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

