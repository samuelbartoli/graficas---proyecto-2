# This sample Makefile allows you to make an OpenGL application
#   whose source is exactly one .c file under linux.
#   check the location of the X libraries on your implementation.
#
# To use this Makefile, you type:
#
#        make xxxx
#                  
# where
#       xxxx.c is the name of the file you wish to compile 
#       
# A binary named xxxx will be produced
# Libraries are assumed to be in the default search paths
# as are any required include files

CC = g++ 
CFLAGS = -g
# OBJECTS 
LDLIBS = -lglut -lGL -lGLU -lX11  -lm -L/usr/X11R6/lib

tron: tron.c 
		$(CC) -g $@.c $(LDLIBS) -o $@

clean: 
	rm tron

