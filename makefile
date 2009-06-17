CXXFLAGS = -lglut -Wall -pedantic -ansi

legion_glut: LEGION.h legion_glut.cpp LEGION.impl
	$(CXX) $(CXXFLAGS)  legion_glut.cpp -o legion_glut

clean:
	$(RM) legion_glut