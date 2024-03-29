#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "TriMesh.h"
//#include "XForm.h"
#include <vector>
#include "nivel.h"

#define SQR(a) (a*a)
#define G 0.1

using namespace std;

int radio = 2;
int x = 3;
int y = 3; 
int z = 0 ;

int rotacion_x = 0;
int rotacion_y = 0;

double sx,sy,sz;
vector<nivel> niveles;
nivel lvlactual;
int vidas,puntaje,enemies;
int init=0;
double lvltime;

/*vector<TriMesh *> meshes;
vector<xform> xforms;
vector<bool> visible;
vector<string> filenames;*/

//rotacion_x = 0 ;
//rotacion_y = 0;

//Maneja el reescalamiento de la ventana
void handleResize(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective(45.0,(double)w / (double)h, 1.0, 200.0) ;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//Settea opciones de opengl
void initRendering() {
    glutInitWindowSize (800, 500); 
    glutInitWindowPosition (400, 50);
    glutCreateWindow ("Tron");    
	glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    glClearColor(0.0,0.0,0.0,0.0);
}

//Manejador para la tecla Esc que cierra la ventana
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

//Procesa el click del mouse
void processMouse(int button, int state, int x, int y){
    float xclick, yclick, depth;
    double pMat[16];
    double mMat[16];
    GLint viewport[4];

    if(GLUT_LEFT_BUTTON==button && GLUT_DOWN==state){
        glGetDoublev(GL_MODELVIEW_MATRIX,mMat);
        glGetDoublev(GL_PROJECTION_MATRIX,pMat);
        glGetIntegerv(GL_VIEWPORT,viewport);

        xclick = x;
        yclick = (float)viewport[3]-(float)y;
        glReadPixels(xclick,yclick,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&depth);

        gluUnProject((double)xclick,(double)yclick,depth,mMat,pMat,viewport,&sx,&sy,&sz);
        printf("xclick=%lf, yclick=%lf, x=%lf, y=%lf, z=%lf \n",xclick,yclick,sx,sy,sz);
    }
}

// Dibuja un cuadrado con los tamanos tamx, tamy , tamz 
// de color r , g, b
// en la posicion posx, posy, posz
// de tipo t , donde :
//  t = 1 : se dibuja un cuadrado paralelo al plano yz
//  t = 2 : se dibuja un cuadrado paralelo al plano xz
//  t = 0 : se dibuja un cuadrado paralelo al plano xy
void dibujarcuadrado(float tamx, float tamy, float tamz, float r, float g, float b, float posx, float posy, float posz, int t, float alpha){
   
    glPushMatrix();
    glTranslatef(posx,posy,posz);
    glBegin(GL_QUADS);
       
        glColor4f(r,g,b,alpha);
        
        switch(t){
        
            case 0: 
                glVertex3f(0,0,0);
                glVertex3f(tamx,0,0);
                glVertex3f(tamx,tamy,0);
                glVertex3f(0,tamy,0);
                break;
            case 1:
                glVertex3f(0,0,0);
                glVertex3f(0,tamy,0);
                glVertex3f(0,tamy,tamz);
                glVertex3f(0,0,tamz);
                break;
            case 2:
                glVertex3f(0,0,0);
                glVertex3f(tamx,0,0);
                glVertex3f(tamx,0,tamz);
                glVertex3f(0,0,tamz);
                break; 
        }

    glEnd();
    glPopMatrix();

}

// Dibuja las aristas del cuadrado de  tamanos tamx, tamy , tamz 
// de color r , g, b
// en la posicion posx, posy, posz
// de tipo t , donde :
//  t = 1 : se dibuja un cuadrado paralelo al plano yz
//  t = 2 : se dibuja un cuadrado paralelo al plano xz
//  t = 0 : se dibuja un cuadrado paralelo al plano xy
void dibujararista(float tamx, float tamy, float tamz, float r, float g, float b, float posx, float posy, float posz, int t, float alpha){
   
    glPushMatrix();
    glTranslatef(posx,posy,posz);
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
        glColor4f(r,g,b,alpha);
        
        switch(t){
        
            case 0: 
                glVertex3f(0,0,0);
                glVertex3f(tamx,0,0);
                glVertex3f(tamx,tamy,0);
                glVertex3f(0,tamy,0);
                break;
            case 1:
                glVertex3f(0,0,0);
                glVertex3f(0,tamy,0);
                glVertex3f(0,tamy,tamz);
                glVertex3f(0,0,tamz);
                break;
           case 2:
                glVertex3f(0,0,0);
                glVertex3f(tamx,0,0);
                glVertex3f(tamx,0,tamz);
                glVertex3f(0,0,tamz);
                break; 
        }

    glEnd();
    glPopMatrix();

}

//Dibuja el area de juego
void dibujarArena(){
    glPushMatrix();
        dibujarcuadrado(100, 0, 100, 0.7, 0.7, 1, -50, -0, -50, 2, 1);
        dibujarcuadrado(0, 20, 100, 0.7, 0.7, 1, -50, 0, -50, 1, 0.5);
        dibujarcuadrado(0, 20, 100, 0.7, 0.7, 1, 50, 0, -50, 1, 0.5);
        dibujarcuadrado(100, 20, 0, 0.7, 0.7, 1, -50, 0 , -50, 0, 0.5);
        dibujarcuadrado(100, 20, 0, 0.7, 0.7, 1, -50, 0 , 50, 0, 0.5);
 
        dibujararista(100, 0, 100, 0, 0, 0, -50, -0, -50, 2, 1);
        dibujararista(0, 20, 100, 0, 0, 0, -50, 0, -50, 1, 1);
        dibujararista(0, 20, 100, 0, 0, 0, 50, 0, -50, 1, 1);
        dibujararista(100, 20, 0, 0, 0, 0, -50, 0, -50, 0, 1);
        dibujararista(100, 20, 0, 0, 0, 0, -50, 0, 50, 0, 1);
    glPopMatrix();
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
    glutSolidCube(5);
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
    glVertex3f(3,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,3,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,3);
    glEnd();
    glPopMatrix();
    
}

float puntos[4][2] = {{0,0},{20,82},{65,30},{70,79}};

//Dibuja las aristas del poligono segun el orden de los puntos en "puntos"
void dibujarpoligono(int tam, float puntos[][2]){
    glPushMatrix();
    glLineWidth(1.5);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<tam;i++){
            glVertex3f(puntos[i][0],2.5,puntos[i][1]);
        }
    glEnd();
    glPopMatrix();
}

void movimiento(double tiempo){
    //Mover los personajes
    for(int i=0;i<4;i++){

        float deltax = obj[i].x-jugadores[i].x;
        float deltaz = obj[i].z-jugadores[i].z;
 
        punto dest;
        dest.x = tiempo*vx[i]+jugadores[i].x;
        dest.z = tiempo*vz[i]+jugadores[i].z;

        if(dest.x-jugadores[i].x>=deltax && dest.z-jugadores[i].z>=deltaz){
            jugadores[i].x=obj[i].x;
            jugadores[i].z=obj[i].z;
            if(){
                obj[i].x=level.
            }
        }

    }  
    //Mover los contrincantes
}

void lanzardisco(int personaje, punto obj){

    punto salida;
    float vi;

    //Calcular la distancia
    float deltax = salida.x-obj.x;
    float deltaz = salida.z-obj.z;
    float dist2 = SQR(deltax)+SQR(deltaz);
    float dist = sqrt(dist2);

    //Calcular el angulo
    float angelev = arcsin((dist*G)/SQR(velocidad inicial del personaje))/2;
    discos[personaje].v.y = sin(angelev)*vi;
    discos[personaje].v.x = (deltax/dist)*(cos(angelev)*vi);
    discos[personaje].v.z = (deltaz/dist)*(cos(angelev)*vi);

    //Inicializo el numero de rebotes
    discos[personaje].rebotes = 0;

    //Mover el disco
        //glutTimerFunc(5000,timerdiscos,1);
}

void timernivel(){
    //Exit del juego
}

void timerdiscos(int personaje){
    //Si un jugador no tiene disco cargo un disco al jugador
}

void update(){
    
    //Mover personajes
    //Mover discos
    //Chequeo el tiempo del nivel
    //Chequear colisiones
}

void iniciodenivel(){
    //Cargar el nivel
    lvlactual=niveles[lvlactual.level_id+1];
    //Cargar los jugadores
    for(int i=0; i<lvlactual.nro_jugadores; i++){
        lvlactual.player[i].ptoactual = lvlactual.player[i].points[0];
        lvlactual.player[i].ptosig = 1;
        lvlactual.player[i].timer = 0;
    }
    //Inicializar las vidas
        vidas = 3;
    //Inicializar el puntaje
        puntaje = 0;
    //Inicializar el tiempo del nivel
        lvltime = lvlactual.game_time;
    //Inicializar el Contador de enemigos
        enemies = lvlactual.nro_jugadores-1;

    glutPostRedisplay(); 
}

//Funcion que dibuja la escena
void dibujar_escena(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(0.0, 0.0, 130.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
    glRotatef(rotacion_x,1,0,0);  
    glRotatef(rotacion_y,0,1,0);  

    //Inicializar
    if(init){
        iniciodenivel();
    }

    //Dibujar Personajes
    punto dib;
    for(int i=0; i < lvlactual.nro_jugadores; i++){

        glPushMatrix();
            switch(i){
                case 0:
                    glColor3f(0,0,1);
                    break;
                case 1:
                    glColor3f(1,0,0);
                    break;
                case 2:
                    glColor3f(0,1,0);
                    break;
                case 3:
                    glColor3f(1,0.6,0);
                    break;
            }

            dibujarpoligono(lvlactual.player[i].nro_puntos, lvlactual.player[i].points);

            dib = lvlactual.player[i].ptoactual;
            glPushMatrix();
                glTranslatef(dib.x,dib.y,dib.z);
                //Aqui se carga la maya
                dibujar_cubo();
            glPopMatrix();
            
        glPopMatrix();
    }

    //Dibujar Obstaculos
    for(int i=0; i < lvlactual.objs.size(); i++){
        dib = lvlactual.objs[i].points;
        glPushMatrix();
            if(lvlactual.objs[i].tipo == 0){
                //Cargar la malla del obstaculo
                glColor3f(0,1,0);
                dibujar_cubo();
            }else if(lvlactual.objs[i].tipo == 1){
                dibujar_cubo();
            }else if(lvlactual.objs[i].tipo == 2){
                dibujar_esfera();
            }
        glPopMatrix();
    }

    //Dibujar Discos
    for(){

    }

    dibujarEjes();
    
    //Dibujar el Tablero
    dibujarArena();
	glutSwapBuffers();
}

int main(int argc, char* argv[]) {

    if(argc<2){
        printf("No se especifico ningun archivo de configuracion\nUso: .\\tron <archivo de configuracion>\n");
        exit(0);
    }

    ParserFile(argv[1],niveles);
    glutInit(&argc,argv);
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
    glutMouseFunc(processMouse);

    iniciodenivel();
    glutTimerFunc(25,update,1);
    glutMainLoop(); 
	return 0;
}
