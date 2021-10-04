CC = g++
COMPILER_FLAGS = -w
SOURCES = ./src/*.cpp
INCLUDES = ./includes/*.hpp
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJ_NAME = game

all: 
	$(CC) $(SOURCES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

