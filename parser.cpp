#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <list>
#include <stdlib.h>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "nivel.h"

using namespace rapidxml;
using namespace std;

void ParserFile(char *filename, vector<nivel> * niveles){

    int i;
    string input_xml;
    string linea;
    ifstream archivo(filename);
    while(getline(archivo,linea))
        input_xml += linea;

    vector<char> buffer(input_xml.begin(), input_xml.end());
    buffer.push_back('\0');
    rapidxml::xml_document<> doc;
    doc.parse<parse_declaration_node | parse_no_data_nodes>(&buffer[0]);
    
    xml_node<> *nodo = doc.first_node("proyecto");

    int nroniveles = atoi(nodo->first_node("niveles")->value());
 
    nodo = nodo->first_node("nivel");  

    //Recorremos los niveles
    for(int i = 0; i < nroniveles ; i++, nodo = nodo->next_sibling("nivel")){
        int puntos = atoi(nodo->first_node("jugador")->first_node("trayectoria")->first_node("puntos")->value());
        //declaramos un nivel
        nivel cn ;
        cn.level_id = atoi(nodo->first_node("id")->value());
        cn.game_time = atoi(nodo->first_node("tiempo_juego")->value());
        
        //JUGADOR
        jugadores jugador(puntos);

        jugador.shot_v = atof(nodo->first_node("jugador")->first_node("disparo")->value());
        jugador.trayec_v = atof(nodo->first_node("jugador")->first_node("trayectoria")->first_node("velocidad")->value());

        jugador.nro_puntos = puntos;

        //pasamos a recorrer los puntos del jugador
        xml_node<> *nodopuntos ; 
        nodopuntos = nodo->first_node("jugador")->first_node("trayectoria")->first_node("punto");

        for(int j = 0; j < puntos && nodopuntos ; j++){
            (jugador.points[j]).x = atof(nodopuntos->first_node("x")->value());
            (jugador.points[j]).y = atof(nodopuntos->first_node("y")->value());
            //printf("x: %f y: %f\n", jugador.points->x, jugador.points->y);
            nodopuntos = nodopuntos->next_sibling("punto");
            
        }  

        //guardamos al jugador
        cn.player[0] = jugador ;
        //printf("holaaa %f\n", cn.player[0].shot_v);

        //CONTRINCANTES
        xml_node<> *nodocon;
        nodocon = nodo->first_node("contrincantes");
        
        int ncontrincantes = atoi(nodocon->value());
        nodocon = nodo->first_node("contrincante");
        
        cn.nro_jugadores = ncontrincantes + 1;
        //recorremos los contrincantes
        for(int k = 1; k <= ncontrincantes ; k ++ , nodocon = nodocon->next_sibling("contrincante")){
            puntos = atoi(nodocon->first_node("trayectoria")->first_node("puntos")->value());
            //Creamos el contrincante
            jugadores cont(puntos);
        
            cont.shot_v = atof(nodocon->first_node("disparo")->value());
            cont.trayec_v = atof(nodocon->first_node("trayectoria")->first_node("velocidad")->value());
            cont.nro_puntos = puntos; 
            nodopuntos = nodocon->first_node("trayectoria")->first_node("punto");
            //recorremos los puntos
            for(int l = 0; l < puntos && nodopuntos ; l++){
                (cont.points[l]).x = atof(nodopuntos->first_node("x")->value());
                (cont.points[l]).y = atof(nodopuntos->first_node("y")->value());
                nodopuntos = nodopuntos->next_sibling("punto");
            }
        
            cn.player[k] = cont ; 
        }

        //OBJETOS
        xml_node<> *objetos ;
        objetos = nodo->first_node("objetos");

        int nobjetos = atoi(objetos->first_node("cantidad")->value());
        
       // printf("hay %d objetos\n", nobjetos);
        objetos = objetos->first_node("objeto");

        for(int j = 0; j < nobjetos ; j++ , objetos = objetos->next_sibling("objeto")){
            string tipo = objetos->first_node()->name();
            
//            obstaculos obs ; 
            obstaculos obs ;
 
            if(!tipo.compare("maya")){
                obs.tipo = 0 ;     
                obs.points.x = atof(objetos->first_node()->first_node("x")->value());      
                obs.points.y = atof(objetos->first_node()->first_node("y")->value());      
         //       printf("x: %f y: %f\n", obs.points.x, obs.points.y);
            }else if (!tipo.compare("cubo")){
                obs.tipo = 1;    
                obs.points.x = atof(objetos->first_node()->first_node("x")->value());      
                obs.points.y = atof(objetos->first_node()->first_node("y")->value());      
           //     printf("x: %f y: %f\n", obs.points.x, obs.points.y);
            }else{
                obs.tipo = 2;    
                obs.points.x = atof(objetos->first_node()->first_node("x")->value());      
                obs.points.y = atof(objetos->first_node()->first_node("y")->value());      
        //        printf("x: %f y: %f\n", obs.points.x, obs.points.y);

            }
        //Insertar el obstaculo en el vector de obstaculos
        (cn.objs).push_back(obs);
 
        }
   
        //Insertamos el nivel en el vector de niveles 
        niveles->push_back(cn);   
    }

}

/*
void print_obstaculos(obstaculos m){
        printf("\n\ttipo: %d\n", m.tipo);
        printf("x: %f y: %f \n", m.points.x , m.points.y);
}   

void print_contrincantes(jugadores m){
    printf("\tdisparo: %f\n", m.shot_v);
    printf("\tvelocidad de trayectoria %f\n", m.trayec_v );

    for(int i = 0; i < m.nro_puntos ; i++){
        printf("\tx: %f y: %f \n", m.points[i].x , m.points[i].y);
    }
}

void print_jugador(jugadores m){
    printf("disparo: %f\n", m.shot_v);
    printf("velocidad de trayectoria %f\n", m.trayec_v );

    for(int i = 0; i < m.nro_puntos ; i++){
        printf("x: %f y: %f \n", m.points[i].x , m.points[i].y);
    }
}

void print_nivel(vector<nivel> l){
    for(int i = 0 ; i < l.size() ; i++){
        printf("\nnivel id: %d\n", l[i].level_id);
        printf("game time: %d\n", l[i].game_time);
        printf("nro jugadores: %d\n", l[i].nro_jugadores);
        
        printf("--- JUGADOR\n");
        print_jugador(l[i].player[0]);

        int j = 1;
        printf("\t--- CONTRINCANTES \n");
        for(int j = 1; j < l[i].nro_jugadores; j++ ){
            printf("el contrincante %d tiene %d puntos \n", j,(int) l[i].player[j].nro_puntos);
            print_contrincantes(l[i].player[j]);
        }

        printf("\t--- OBSTACULOS: %d\n",(int) l[i].objs.size());
        for(int k = 0; k < (int)l[i].objs.size() ; k++){
            print_obstaculos(l[i].objs[k]);
        }
    }
}

int main (int argc, char * argv[]){

    vector<nivel> niveles;   

    ParserFile("config2.xml",&niveles);
    int tamano = niveles.size();

    print_nivel(niveles);
}
*/

