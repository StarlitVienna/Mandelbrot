OBJS = *.cpp
CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = -std=c++20 -lSDL2 -lSDL2_image -fext-numeric-literals
OBJ_NAME = main
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME); ./main
