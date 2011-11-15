#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TriMesh.h"
#include "XForm.h"
#include <vector>

using namespace std;


int radio = 2;
int x = 3;
int y = 3; 
int z = 0 ;

int rotacion_x = 0;
int rotacion_y = 0;

vector<TriMesh *> meshes;
vector<xform> xforms;
vector<bool> visible;
vector<string> filenames;

//rotacion_x = 0 ;
//rotacion_y = 0;

void manejador_teclas(unsigned char key, 
					int x, int y) {
	switch (key) {
    	case 27: 
			exit(0); 
    }
}   

//mover camara
void move_cam(int key, int x, int y){
    switch(key) {
        case GLUT_KEY_RIGHT:
            rotacion_y += 2 ;
            break;
        case GLUT_KEY_LEFT:
            rotacion_y -= 2;
            break;
        case GLUT_KEY_UP:
            rotacion_x += 2;
            break;
        case GLUT_KEY_DOWN:
            rotacion_x -= 2;
            break;
    }  
    glutPostRedisplay();

}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
}


void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective(45.0,(double)w / (double)h, 1.0, 200.0) ;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


//dibuja una esfera
void dibujar_esfera(){
    glPushMatrix();
    glTranslatef(-4,-2,0);
    glColor3f(1.2,1.5,2);
    glutSolidSphere(radio,100,100);
    glPopMatrix();
}

//dibujar un cubo
void dibujar_cubo(){
    glPushMatrix();
    glRotatef(45,0,1,0);
    glTranslatef(10,y,z);
    glColor3f(1,0,0);
    glScalef(1,1,1);
    glutSolidCube(4);
    glColor3f(0,0,0);
    glutWireCube(4);
    glPopMatrix();
}





//Dibujar los ejes de plano
void dibujarEjes(){
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(10,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,10,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,10);
    glEnd();
    glPopMatrix();
    
}


//Funcion que dibuja la escena
void dibujar_escena() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(0.0, 0.0, 85.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
    glRotatef(rotacion_x,1,0,0);  
    glRotatef(rotacion_y,0,1,0);  
    dibujarEjes(); 
    dibujar_esfera();
    dibujar_cubo();
    
	glutSwapBuffers();

}


int main(int argc, char* argv[]) {

    glutInit(&argc,argv);
    glutInitWindowSize (800, 500); 
    glutInitWindowPosition (400, 50);
    glutCreateWindow ("Tron");    
	initRendering(); 
/*
    const char *filename = argv[1];
    TriMesh *themesh = TriMesh::read(filename);
    //if(!themesh)
      //  usage(argv[0]);


    themesh->need_normals();
    themesh->need_tstrips();
    themesh->need_bsphere();
    meshes.push_back(themesh);
    xforms.push_back(xform());
    visible.push_back(true);
    filenames.push_back(filename); 
*/

    glutDisplayFunc(dibujar_escena);
	
    glutKeyboardFunc(manejador_teclas);
    glutSpecialFunc(move_cam);
	glutReshapeFunc(handleResize);
//    glutTimerFunc(10,move_cam,1);
    glutMainLoop(); 
	return 0;
}
