CC = g++ 
PROG =  tron

LIBS = -Itrimesh/include -Ltrimesh/lib.Linux64 
LDLIBS = -lglut -lGL -lGLU -lX11 -lm -ltrimesh -ljpeg -L"/usr/X11R6/lib"

$(PROG): tron.cpp 
	$(CC) $(LIBS) $(LDLIBS) tron.cpp -o $(PROG)

clean: 
	rm tron

