CC = g++

# Optimisation level
OPT     = -Ofast

# some flags
FLAGS   = -fno-strict-aliasing -fexceptions -I/usr/include

## few locations
INC_DIR	  = ./

## final compilation flags
CFLAGS	= $(OPT) $(FLAGS) -Wall -I$(INC_DIR)

# OpenCV libraries
PKG_CONFIG_CFLAGS=`pkg-config --cflags opencv`

# OpenCV libraries
PKG_CONFIG_LIB=`pkg-config --libs opencv`

# EXECcutable
EXEC = ./bin/birdseye

# Main
MAIN = main

# Objects to be linked with main
OBJS = birdseyeperspective.o

# Compilation command
$(EXEC) : $(MAIN).cpp ${OBJS}
	$(CC) $(RPATH) $(CFLAGS) $(PKG_CONFIG_CFLAGS) $(MAIN).cpp ${OBJS} -o $(EXEC) $(PKG_CONFIG_LIB) $(LIB)

birdseyeperspective.o: birdseyeperspective.cpp birdseyeperspective.hpp
	$(CC) -c $(CFLAGS) $(PKG_CONFIG_CFLAGS) birdseyeperspective.cpp 

clean: 
	rm -f ${EXEC} ${OBJS}