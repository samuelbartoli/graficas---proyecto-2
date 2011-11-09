CC = g++ 
PROG =  tron

LIBS = -I"./trimesh2/include" -I"./trimesh2/include/GL" -L"./trimesh2/lib.Linux64" 
LDLIBS = -lglut -lGL -lGLU -lX11 -lm -ltrimesh -ljpeg -L"/usr/X11R6/lib"

$(PROG): tron.cpp 
	$(CC) $(LIBS) $(LDLIBS) tron.cpp -o $(PROG)

clean: 
	rm tron

