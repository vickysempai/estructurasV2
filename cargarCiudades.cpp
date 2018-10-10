#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "ABB(ciudades)/Binario.cpp"

using namespace std;

void insertarCiudad(Binario &arbol, string datos) {
	string codigo, ciudad;
	bool bandera = false;
	for (int i = 0; i < datos.length(); i++) {
		if (datos[i] != *";") {
			if (!bandera) {
				codigo.operator+=(datos[i]);
			}
			else {
				ciudad.operator+=(datos[i]);
			}
		}
		else {
			bandera = true;
		}
	}
	if (!arbol.buscar(codigo)) {
		arbol.InsertaNodo(codigo,ciudad);
	}
}

Binario leerCiudades(string file_name) {
	string STRING;
	ifstream infile;
	infile.open(file_name);
    Binario arbol;
	while (!infile.eof()) {
		getline(infile, STRING);
		insertarCiudad(arbol, STRING);
    }
    infile.close();
    return arbol;
}

/*int main(int argc, char const *argv[]) {
    Binario ciudades = leerCiudades("archivos_txt/Ciudad.txt");
	cout << "Postorden: ";
    PostordenR(ciudades.raiz);
	cout << endl;
	cout << "Preorden: ";
	PreordenR(ciudades.raiz);
	cout << endl;
	cout << "Inorden: ";
	InordenR(ciudades.raiz);
	cout << endl;
	//cin.get();
	return 0;
}*/

