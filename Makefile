CC = g++
COMPILER_FLAGS = -w
SOURCES = ./src/*.cpp
INCLUDES = ./include/
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJ_NAME = ./build/game

all: 
	$(CC) $(SOURCES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -I $(INCLUDES) -o $(OBJ_NAME)

