#ifndef ARBOLAA_H
#define ARBOLAA_H

#include <cstddef>
#include <iostream>
#include "NodoAA.h"
class ArbolAA
{
public:
	NodoAA *raiz;
	ArbolAA()
	{
		raiz = NULL;
	}
	int insertar(string pCodSuper,string pCodProducto,string pNombre,int pCant,float pPrecio);
	void giro(NodoAA *r);
	bool Vacio(NodoAA *r){return r == NULL;}
	bool reparto(NodoAA *);
	void rebalancear(NodoAA *);
	NodoAA *insertarAux(NodoAA *,NodoAA *);
	NodoAA *buscar(string c);
	int contNodoAA(NodoAA *);
	void mostrar(NodoAA *actual);
	void toString(NodoAA *actual,string &msg);
};

#endif
