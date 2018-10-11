#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "RN(supers)/ArbolRyN.cpp"
#include "cargarCiudades.cpp"

using namespace std;

void insertarSuper(RyN &arbol,Binario &ciudades, string datos) {
	string codigo, codCiudad, nombre;
	bool bandera1 = false;
	bool bandera2 = false;
	for (int i = 0; i < datos.length(); i++) {
		if (datos[i] != *";") {
			if (!bandera1) {
				codCiudad.operator+=(datos[i]);
			}
			else if (!bandera2) {
				codigo.operator+=(datos[i]);
			}
			else {
				nombre.operator+=(datos[i]);
			}
		}
		else if (!bandera1) {
			bandera1 = true;
		}
		else {
			bandera2 = true;
		}
	}
	if (ciudades.buscar(codCiudad) && (arbol.buscar(codigo) == NULL)) {
		arbol.insercion(codCiudad,codigo,nombre);
	}
}

void insertarProducto(RyN &arbol,Binario &ciudades, string datos) {
	string codSuper, codigo, nombre, cantidad, precio;
	bool bandera1 = false;
	bool bandera2 = false;
	bool bandera3 = false;
	bool bandera4 = false;
	for (int i = 0; i < datos.length(); i++) {
		if (datos[i] != *";") {
			if (!bandera1) {
				codSuper.operator+=(datos[i]);
			}
			else if (!bandera2) {
				codigo.operator+=(datos[i]);
			}
			else if (!bandera3) {
				nombre.operator+=(datos[i]);
			}
			else if (!bandera4) {
				cantidad.operator+=(datos[i]);
			}
			else {
				precio.operator+=(datos[i]);
			}
		}
		else if (!bandera1) {
			bandera1 = true;
		}
		else if (!bandera2) {
			bandera2 = true;
		}
		else if (!bandera3) {
			bandera3 = true;
		}
		else {
			bandera4 = true;
		}
	}
	if ((arbol.buscar(codSuper) != NULL) && ((arbol.buscar(codSuper)->inventario->buscar(codigo))) == NULL) {
		arbol.insertarProducto(codSuper, codigo, nombre, stoi(cantidad), stof(precio));
	}
}

void leerArchivo(RyN &arbol,Binario &ciudades,string file_name, int tipo) {
	string STRING;
	ifstream infile;
	infile.open(file_name);
	while (!infile.eof()) {
		getline(infile, STRING);
		switch (tipo) {
		case 0:
			insertarSuper(arbol,ciudades, STRING);
			break;
		case 1:
			insertarProducto(arbol,ciudades, STRING);
			break;
		}
	}
	infile.close();
}

int main(int argc, char const *argv[]) {
    Binario ciudades = leerCiudades("archivos_txt/Ciudad.txt");
	RyN supers;
    leerArchivo(supers,ciudades,"archivos_txt/supermercado.txt",0);
    leerArchivo(supers,ciudades,"archivos_txt/Inventariodatos.txt",1);
    //ciudades.PreordenI(ciudades.raiz);
    supers.mostrar(supers.primeroRN);
	//cin.get();
	return 0;
}