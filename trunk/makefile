CXXFLAGS =  -Wall -pedantic -ansi -I/usr/local/include
LIBS=-lglut

legion_glut: LEGION.h legion_glut.cpp LEGION.impl
	$(CXX) $(CXXFLAGS)  legion_glut.cpp LEGION.h -o legion_glut $(LIBS)

clean:
	$(RM) legion_glut