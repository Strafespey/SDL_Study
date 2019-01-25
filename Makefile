#OBJS specifies which files to compile
OBJS = 08_geometry_rendering.cpp

#CC specifies the compiler
CC = g++

#INCLUDE_PATHS specifies the additional include paths
INCLUDE_PATHS = -IC:\mingw_dev_lib\include\SDL2

#LIBRARY PATHS specifies additional library paths needed
LIBRARY_PATHS = -LC:\mingw_dev_lib\lib

#COMPILER_FLAGS specifies the additional compilations options
COMPILER_FLAGS = -w -Wl,-subsystem,windows

#LINKER_FLAGS specifies libraries that we are linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of the executable
OBJ_NAME = a.out

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
