#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "nodoUsuario.h"
#include "ArbolB.h"

using namespace std;
//nodoUsuario us4("00",11,"Juan Perez","5874569",1);
void insertarUsuario(ArbolB &arbol, string linea) {
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
	nodoUsuario nuevo(atributos[0],atributos[1],atributos[2],atributos[3],atributos[4]);
	arbol.insertar(nuevo);
}

ArbolB leerUsuarios(string archivo) {
	string line;
	ifstream myfile (archivo.c_str());
	ArbolB arbol;
	if (myfile.is_open())
	{ 
		while ( getline (myfile,line) )
		{
			insertarUsuario(arbol,line);  
		}
		myfile.close();
	}
	else cout << "Unable to open file"; 
	
	return arbol;
}
/*****************
nodoinventario(string linea)
{
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
	}
	CodSuper=atributos[0];
	CodProducto=atributos[1];
	Nombre=atributos[2];
	CantidadProducto=atributos[3];
	PrecioUnitario=atributos[4];
	siguiente = NULL;
	anterior = NULL;
}

void listaDCinventario::leerarchivo(string archivo){
	string line;
	ifstream myfile (archivo.c_str());
	if (myfile.is_open())
	{ 
		while ( getline (myfile,line) )
		{
			InsertarFinal(line);  
		}
		myfile.close();
	}
	else cout << "Unable to open file"; 
}
//////////////*************/
int main(int argc, char const *argv[])
{
    ArbolB usuarios = leerUsuarios("../archivos_txt/Usuarios.txt");
    usuarios.escribir();
    //cin.get();
return 0;
}


