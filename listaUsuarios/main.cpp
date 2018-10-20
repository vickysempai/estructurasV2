#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "nodoUsuario.h"
#include "listaDC.h"
//#include "pch.h"
//#include ""

using namespace std;
//nodoUsuario us4("00",11,"Juan Perez","5874569",1);
void insertarUsuario(ArbolB *arbol, string linea,avlTree *usuario3) {
	string codCiudad,cedula,nombre,telefono,tipo;
	bool bandera = false;
	
	char str[linea.size()+1];
	strcpy(str,linea.c_str());
	char * pch;
	pch = strtok (str,";");
	string atributos[5];
	int cont=0;
	while (pch != NULL)
	{
		atributos[cont]=pch;
		pch = strtok (NULL, ";");
		cont++;
	}/*
	string cc=atributos[0];
	string ced=atributos[1];
	string nombre=atributos[2];
	string telefono=atributos[3];
	atributos[4]<<atributos[5]<<endl;*/
	
	if(atributos[4]=="3")
	{
		usuario3->insert(atributos[0],atributos[1],atributos[2],atributos[3]);
	}
	else
	{
		nodoUsuario nuevo(atributos[0],atributos[1],atributos[2],atributos[3],atributos[4]);
		arbol->insertar(nuevo);
		
	}
}

void leerUsuarios(string archivo,avlTree *usuario3,ArbolB* usuarios) {
	string line;
	ifstream myfile(archivo.c_str());
	if (myfile.is_open())
	{ 
		while ( getline (myfile,line) )
		{
			insertarUsuario(usuarios,line,usuario3);  
		}
		myfile.close();
	}
	else cout << "Unable to open file"; 
}
	
avlTree* usuario3= new avlTree();		
ArbolB* usuarios= new ArbolB();

int main(int argc, char const *argv[])
{
	
	leerUsuarios("../archivos_txt/Usuarios.txt",usuario3,usuarios);
	usuarios->escribir();
	listaDC a;
	a.InsertarInicio("0");
	a.InsertarInicio("1");
	a.InsertarInicio("2");
	a.InsertarInicio("3");
	a.agregarArbol(usuarios,usuario3);
    //cin.get();
return 0;
}


