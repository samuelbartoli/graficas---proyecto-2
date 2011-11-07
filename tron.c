#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
//#include "Trimesh.h"

<<<<<<< HEAD
//HOLAAA

=======
//algo
>>>>>>> origin/master
int comienzo = 0;
int velocidad_x, velocidad_z, bar_x;

int radio = 2;
int x = 3;
int y = 3; 
int z = 0 ;

void manejador_teclas(unsigned char key, 
					int x, int y) {   
	switch (key) {
	case 27: 
			exit(0); 
            break;
    case 32: 
        if(!comienzo){
//            srand48(time(NULL));
            const float PI = acos(-1) ; 
            float alpha = (drand48() * 10 ) + 85;
            alpha = alpha*PI/180;
            velocidad_x = (drand48() * 0.1) +0.1 ;
            velocidad_x = (drand48()>0.5) ? -velocidad_x : velocidad_x;

            float h = velocidad_x / cos(alpha*PI/180);
            velocidad_z = sin(alpha)*h;
 
        }
        comienzo = 1;
    }
    glutPostRedisplay();
}


//mover jugador
void direccionales(int key, int x, int y){
    switch(key) {
        case GLUT_KEY_RIGHT:
            bar_x = (bar_x + 13 >= 50) ? 40 : bar_x + 3;
            break;
        case GLUT_KEY_LEFT:
             bar_x = (bar_x -3 <= 0) ? 0 : bar_x -3;
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

//dibujar cubo
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

//Funcion que dibuja la escena
void drawScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(0.0, 0.0, 85.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
    
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
    glutDisplayFunc(drawScene);
	glutKeyboardFunc(manejador_teclas);
    glutSpecialFunc(direccionales);
	glutReshapeFunc(handleResize);

   // glutTimerFunc(10,dibujar_esfera,1);
	
    glutMainLoop(); 
	return 0;
}
