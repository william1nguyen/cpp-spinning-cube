# Compiler
CXX = g++

# C++ Standard version
CXX_STD = c++11

# Compiler flags
CXXFLAGS = -Wall -g --std=${CXX_STD}

# Target executable
TARGET = main

# Source files
SRC = src/main.cpp

build:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)
start:
	./$(TARGET)
clean:
	rm -rf $(TARGET) $(TARGET).dSYM
dev:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) && ./$(TARGET) && make clean