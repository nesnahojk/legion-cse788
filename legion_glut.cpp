//Keith Johansen
//CSE 788.02 Spring 2009
//LEGION -- Locally Excitatory Globally Inhibitory Neuron, Wang and Terman 1995

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>
#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "LEGION.h"




using namespace std;

LEGION<> *  OHIO_LEGION;
bool draw = false;


void KeyboardFunc(unsigned char key, int x, int y) {
    if (key == ' ') {
        draw = !draw;
    } else if (key == 27) {
        exit(1);
    }
}



void processSpecialKeys(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_HOME:
	  OHIO_LEGION->Reset(0,1,0,1);
    }
}



// Initialize OpenGL's rendering modes
void initRendering() {
    glEnable(GL_DEPTH_TEST);

    glPointSize(8);
    glLineWidth(5);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void drawLEGION() {
    double max = OHIO_LEGION->Max_X_Grid();
    double min = OHIO_LEGION->Min_X_Grid();

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    float posx;
    float posy;


    double diff = 0.0f, col = 0.0f;
    double sep = 1.0 / (float) OHIO_LEGION->N;

    glBegin(GL_QUADS);
    for (int i = 1; i <= OHIO_LEGION->N; i++) {
        posx = -1 + sep * i * 1.85;
        for (int j = 1; j <= OHIO_LEGION->N; j++) {
            col = (OHIO_LEGION->legion_nodes[i][j].x - min) / (max - min);
            diff = col * .02 + .01;
            if (OHIO_LEGION->legion_nodes[i][j].I > 0) {
                cout << col << " ";
            }
            posy = 1 - sep * j * 1.85;
            glColor3f(0, col, 0);
            glVertex3f(posx - diff, posy - diff, 0.0f);
            glVertex3f(posx + diff, posy - diff, 0.0f);
            glVertex3f(posx + diff, posy + diff, 0.0f);
            glVertex3f(posx - diff, posy + diff, 0.0f);
        }
    }
    cout << OHIO_LEGION->z;
    cout << endl;

    glEnd();
    glutSwapBuffers();
}


void loop() {
    if (draw == true) {
        OHIO_LEGION->Iteration(.2);
        glutPostRedisplay();
        glutSwapBuffers();
    }
}

int main(int argc, char *argv[]) {


  
    srand(time(NULL));
    string s;
    getline(cin,s);


    OHIO_LEGION=new LEGION<>(atoi(s.c_str()));

    


    if (getline(cin, s) != NULL) {
    cout<<s<<endl;
        for (int i = 1; i <= OHIO_LEGION->N; i++) {
            for (int j = 1; j <= OHIO_LEGION->N; j++) {
                //take the input from stdin and put into legion inputs
	      OHIO_LEGION->legion_nodes[i][j].I = (s[(j - 1) * OHIO_LEGION->N + i - 1] - '0')*.22 - .02;
                
                //give a random range to start
	      OHIO_LEGION->legion_nodes[i][j].x = OHIO_LEGION->Rand_Range(0, 1);
              OHIO_LEGION->legion_nodes[i][j].y = OHIO_LEGION->Rand_Range(0, 1);
            }
        }

    }

    OHIO_LEGION->Init_Weights(6.0, 1.5);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(20, 60);
    glutInitWindowSize(720, 720);
    glutCreateWindow("LEGION");

    initRendering();

    glutKeyboardFunc(KeyboardFunc);
    glutSpecialFunc(processSpecialKeys);

    glutDisplayFunc(drawLEGION);

    glutIdleFunc(loop);
    glutMainLoop();


    delete(OHIO_LEGION);
    return (0);

}





