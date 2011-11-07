CC = g++ 
CFLAGS = -g
# OBJECTS 
LDLIBS = -lglut -lGL -lGLU -lX11  -lm -L/usr/X11R6/lib

tron: tron.c 
		$(CC) -g $@.c $(LDLIBS) -o $@

clean: 
	rm tron

