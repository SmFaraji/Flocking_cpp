# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20

# SDL2 library
LDFLAGS = -lSDL2

# Target executable
TARGET = flock

# Source files
SRC = main.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Dependencies
DEPS = myLib.h screen.h

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Rule to build object files and track dependencies
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(TARGET) $(OBJ)
