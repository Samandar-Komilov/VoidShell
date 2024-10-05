CC = g++
CFLAGS = -Wall -g
TARGET = build/voidsh

SRC = src/main.cpp src/command_parser.cpp src/executor.cpp src/signal_handlers.cpp
OBJ = $(SRC:src/%.cpp=obj/%.o)

# Default target: builds the executable
all: $(TARGET)

# Create build and obj directories if they don't exist
$(TARGET): $(OBJ)
	@mkdir -p build  # Ensure build/ directory exists
	$(CC) -o $(TARGET) $(OBJ) $(CFLAGS)

# Rule to generate object files in obj/ directory
obj/%.o: src/%.cpp
	@mkdir -p obj    # Ensure obj/ directory exists
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean up only the obj/ directory and the executable
clean:
	rm -f obj/*.o
