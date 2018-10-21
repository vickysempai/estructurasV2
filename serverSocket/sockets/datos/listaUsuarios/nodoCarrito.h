#ifndef NODOCARRITO_H
#define NODOCARRITO_H
#include <iostream>

using namespace std;

class nodoC {
	public:
		nodoC(string pNombre, int pCant, float pPrecio)
		{
			nombre = pNombre;
			cantidad = pCant;
			precio = pPrecio;
			siguiente = NULL;
		}

		nodoC(string pNombre, int pCant, float pPrecio, nodoC * signodo)
		{
			nombre = pNombre;
			cantidad = pCant;
			precio = pPrecio;
			siguiente = signodo;
        }
	
		string nombre;
		int cantidad;
		float precio;
		nodoC *siguiente;
};

typedef nodoC *pnodoC;

#endif NODOCARRITO_H