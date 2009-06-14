legion.o: 
	g++ LEGION.h legion_glut.cpp -lglut -o legion.o
clean:
	rm legion.o