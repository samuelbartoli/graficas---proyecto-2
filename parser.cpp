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

nivel *n;

list<nivel> lista;

int main(int argc, char *argv[]){

    int i;
    string input_xml;
    string linea;
    ifstream archivo("config2.xml");
    while(getline(archivo,linea))
        input_xml += linea;

    vector<char> buffer(input_xml.begin(), input_xml.end());
    buffer.push_back('\0');
    rapidxml::xml_document<> doc;
    doc.parse<parse_declaration_node | parse_no_data_nodes>(&buffer[0]);

    xml_node<> *nodo = doc.first_node("proyecto");
    int nniveles  = atoi(nodo->first_node("niveles")->value());
    cout << "Niveles: " << nniveles << endl; 

    for(xml_node<> *atributos = nodo->first_node("nivel")->first_node(); 
            atributos ; atributos = atributos->next_sibling()){
        if(!strcmp(atributos->name(),"jugador")){
            xml_node<> * attr_player = atributos->first_node();
            cout <<  attr_player->name() << endl;
            cout << attr_player->value() << endl;
        }else{
            cout <<  atributos->name() << endl;
            cout << atributos->value() << endl;
        }
    }


    return 0;
}
