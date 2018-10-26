#ifndef NodoAA_H
#define NodoAA_H

#include <cstddef>
#include <string>
using namespace std;

class NodoAA
{
public:
	NodoAA(string pCodSuper,string pCodProducto,string pNombre,int pCant,float pPrecio){
		codSuper = pCodSuper;
		codProducto = pCodProducto;
		nombre = pNombre;
		cantidad = pCant;
		precioU = pPrecio;
		cantidadProducto = 0;
	}
	int cantidadProducto;
	int cont, nivel, cantidad;
	float precioU;
	string codSuper,codProducto,nombre;
	NodoAA *derecha;
	NodoAA *izquierda;
	NodoAA *padre;
	NodoAA *raiz;
};

#endif
