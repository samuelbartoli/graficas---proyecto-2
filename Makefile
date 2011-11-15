CC = g++ 
PROG =  tron

LIBS = -Itrimesh2/include -Ltrimesh2/lib.Linux64 
LDLIBS = -lglut -lGL -lGLU -lX11 -lm -ltrimesh -ljpeg -L"/usr/X11R6/lib"

$(PROG): tron.cpp 
	$(CC) $(LIBS) $(LDLIBS) tron.cpp -o $(PROG)

clean: 
	rm tron

