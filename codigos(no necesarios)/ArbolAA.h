#ifndef ARBOLAA_H
#define ARBOLAA_H

#include <cstddef>
#include <iostream>
#include "NodoAA.h"
class ArbolAA
{
protected:
	NodoAA *raiz;
public:
	ArbolAA()
	{
		raiz = NULL;
	}
	int insertar(int cod, string sinn);
	void giro(NodoAA *);
	bool Vacio(NodoAA *r){return r == NULL;}
	bool reparto(NodoAA *);
	void rebalancear(NodoAA *);
	NodoAA *insertarAux(NodoAA *,NodoAA *);
	NodoAA *buscar(int c);
	int contNodoAA(NodoAA *);
};

#endif
